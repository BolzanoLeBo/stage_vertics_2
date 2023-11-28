
import gurobipy as gp
from gurobipy import GRB

from multiprocessing import Pool
from csv import writer
import os
import time
from math import floor
def solver(taskset) : 
    n = len(taskset)
    start_time = time.perf_counter()

    model = gp.Model("ilp_ram_allocator")
    model.setParam('OutputFlag', 0)
    model.setParam('TimeLimit', 3600)
    model.setParam('Threads', 1)

    x_f = model.addVars(n,12, vtype = GRB.BINARY)
    x_p = model.addVars(n,2, vtype = GRB.BINARY)
    x_ro = model.addVars(n,4, vtype = GRB.BINARY)
    x_prec = model.addVars(n,4, vtype = GRB.BINARY)
    x_c = model.addVars(n,384, vtype = GRB.BINARY)

    #indexs for each memory allocations 
    c_instr_flash = [c for c in range(384) if (c - 32*floor(c/32)) in range(0,15)]
    c_instr_ccm = [c for c in range(384) if (c - 32*floor(c/32)) in range(16,32)]
    c_ro_flash = []
    c_ro_ccm = []
    c_ro_ram = []
    for c in range (384) : 
        f_i = floor(c/32)
        t = c-32*f_i
        c_i = floor((t)/16)
        t = t - 16*c_i
        ro_i = floor((t)/4)

        if ro_i == 1 : 
            c_ro_flash.append(c)
        elif ro_i == 2 : 
            c_ro_ram.append(c)
        elif ro_i == 3 : 
            c_ro_ccm.append(c)

    #var dimension 
    #no multiple allocation
    model.addConstrs(gp.quicksum(x_c[i,c] for c in range(384) )== 1 for i in range(n))

   #FLASH size constraint
    #we can have instruction or ro data
    #if c in [0,7]U[16,23]U[32, 39] for instruction in FLASH (c - 16*floor(c/16)) in [0,7]  
    #if c in {1, 5, 9, ... , 45} c%4 = 1  ro in FLASH
    model.addConstr(gp.quicksum((taskset[i].size_i * int(c in c_instr_flash) * x_c[i,c] + 
                                taskset[i].size_ro * int(c in c_ro_flash) * x_c[i,c]) 
                                for c in range(384)  
                                for i in range(n)) <= taskset.flash_size)
    #CCM size constraint
    #we can have instruction or ro data
    model.addConstr(gp.quicksum((taskset[i].size_i*int(c in c_instr_ccm)* x_c[i,c]+
                                taskset[i].size_ro *int(c in c_ro_ccm)* x_c[i,c])
                                for c in range(384)
                                for i in range(n)) <= taskset.ccm_size)
    #SRAM size constraint 
    #we can have input data or ro data 
    model.addConstr(gp.quicksum(taskset[i].size_ro * int(c in c_ro_ram) * x_c[i,c]
                                #+ taskset[i].size_d * x_d[i,1]
                                for c in range(384)
                                for i in range(n)) <= taskset.ram_size)
    
    
    #utilization less than 1 
    model.addConstr(gp.quicksum((taskset[i].perf2[c][0]/taskset[i].period)*x_c[i,c] 
                for c in range (384)
                for i in range (n)
                ) <= 1 )

    #minimize the energy
    model.setObjective(
    gp.quicksum((taskset[i].perf2[c][1]/taskset[i].period)*x_c[i,c]
                for c in range (384)
                for i in range (n))
    ,
    GRB.MINIMIZE)

    end_time = time.perf_counter()
    create_time = end_time - start_time 

    start_time = time.perf_counter()
    model.optimize()
    end_time = time.perf_counter()
    run_time = end_time - start_time

    #print("times : ", create_time, run_time)

    
    if model.Status == GRB.INF_OR_UNBD:
        raise Exception('Model is infeasible or unbounded')
    elif model.Status == GRB.INFEASIBLE:
        raise Exception('Model is infeasible')
    elif model.Status == GRB.UNBOUNDED:
        raise Exception('Model is unbounded')
    x_c_sol = model.getAttr("x", x_c)


    #read results
    f_str = ["16_RANGE2", "26_RANGE2", "16", "26", "30", "60", "90", "120", "150", "170", "150_BOOST", "170_BOOST"]
    c_str = ["code Flash", "code CCM"]
    prec_str = ["cache on prefetch on", "cache on prefetch off", "cache off prefetch on", "cache off prefetch off"]
    ro_str = ["no ro", "ro FLASH", "ro RAM", "ro CCM"]
    U_tot = 0
    E_tot = 0
    E_ref = 0

    ccm_used = 0
    flash_used = 0
    ram_used = 0
    f_ccm = {}
    f_flash = {}
    nb_instr_ccm = 0
    nb_instr_flash = 0
    nb_prefetch = 0
    nb_cache = 0

    for i in range (n) : 
        config = 0
        f_i = 0
        for c in range (384) : 
            if x_c_sol[i,c] > 0.5 : 
                config = c
                f_i = floor(c/32)
                t = c-32*f_i
                c_i = floor((t)/16)
                t = t - 16*c_i
                ro_i = floor((t)/4)
                t = t - 4*ro_i
                prec_i = floor((t)/1)
                
        #if code in flash 
        if config in c_instr_flash : 
            flash_used += taskset[i].size_i
            nb_instr_flash += 1
            if f_str[f_i]+'f' in f_flash : 
                f_flash[f_str[f_i]+'f'] += 1
            else : 
                f_flash[f_str[f_i]+'f'] = 1
        #if code in CCM
        elif config in c_instr_ccm: 
            ccm_used += taskset[i].size_i
            nb_instr_ccm += 1 
            if f_str[f_i]+'c' in f_ccm : 
                f_ccm[f_str[f_i]+'c'] += 1
            else : 
                f_ccm[f_str[f_i]+'c'] = 1
        #ro configuration
        if config in c_ro_flash: 
            flash_used += taskset[i].size_ro
        elif config in c_ro_ram : 
            ram_used += taskset[i].size_ro
        elif config in c_ro_ccm :
            
            ccm_used += taskset[i].size_ro

        #calculate task utilization
        util = taskset[i].perf2[config][0]/taskset[i].period
        U_tot += util
        #calculate task energy
        energy = taskset[i].perf2[config][1]
        
        E_tot += energy/taskset[i].period
        E_ref += taskset[i].ref_energy/taskset[i].period

        
    #    print(taskset[i].name, f_str[f], c_str[c], prec_str[prec], ro_str[ro])
    #print(nb_cache, nb_prefetch, nb_instr_flash, nb_instr_ccm) 
    #print (U_tot, E_ref, E_tot)
    #calculate the utilization gain and energy gain
    U_gain = float((taskset.u_tot - U_tot)/taskset.u_tot)
    E_gain = (E_ref-E_tot)/E_ref
    
    f_keys = []
    f_values = []
    for key in f_str : 
        keyc = key+"c"
        keyf = key+"f"
        f_keys.append(keyc)
        f_keys.append(keyf)
        if keyc in f_ccm :
            f_values.append(f_ccm[keyc]/n)
            f_ccm[keyc] = f_ccm[keyc]/n
        else :
            f_values.append(0)
            f_ccm[keyc] = 0
        if keyf in f_flash :
            f_values.append(f_flash[keyf]/n)
            f_flash[keyf] = f_flash[keyf]/n
        else : 
            f_values.append(0)
            f_flash[keyf] = 0

    res = [U_gain, E_gain]+f_values
    f_exists = os.path.exists('results/stm32g/{}.csv'.format(n))
    with open('results/stm32g/{}.csv'.format(n), 'a') as file:
        w = writer(file,delimiter="\t" )
        if not f_exists : 
           # w.writerow(["U_gain", "E_gain", "flash_ratio", "ram_ratio", "ccm_ratio"]+list(f_ccm.keys())+list(f_flash.keys()))
           w.writerow(["U_gain", "E_gain"]+f_keys)
        w.writerow(res)
    return run_time


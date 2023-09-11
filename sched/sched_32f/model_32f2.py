
import gurobipy as gp
from gurobipy import GRB
from csv import writer
import os
from multiprocessing import Pool
from copy import deepcopy
from math import floor
import time
def solver(taskset) : 
    start_time = time.perf_counter()
    n = len(taskset)
    
    model = gp.Model("ilp_ram_allocator")
    model.setParam('OutputFlag', 0)
    model.setParam('TimeLimit', 3600)
    model.setParam('Threads', 1)

    #indexs for each memory allocations 
    c_instr_flash = [c for c in range(48) if (c - 16*floor(c/16)) in range(0,8)]
    c_ro_flash = [c for c in range(48) if c%4 == 1]
    c_instr_ccm = [c for c in range(48) if (c - 16*floor(c/16)) in range(8,16)]
    c_ro_ccm = [c for c in range(48) if c%4 == 3]
    c_ro_ram = [c for c in range(48) if c%4 == 2]

    x_c = model.addVars(n,48, vtype = GRB.BINARY)

    #var dimension 
    #no multiple allocation
    model.addConstrs(gp.quicksum(x_c[i,j] for j in range(48) )== 1 for i in range(n))

    #FLASH size constraint
    #we can have instruction or ro data
    #if c in [0,7]U[16,23]U[32, 39] for instruction in FLASH (c - 16*floor(c/16)) in [0,7]  
    #if c in {1, 5, 9, ... , 45} c%4 = 1  ro in FLASH
    model.addConstr(gp.quicksum((taskset[i].size_i * int(c in c_instr_flash) * x_c[i,c] + 
                                taskset[i].size_ro * int(c in c_ro_flash) * x_c[i,c]) 
                                for c in range(48)  
                                for i in range(n)) <= taskset.flash_size)
    #CCM size constraint
    #we can have instruction or ro data
    #if c in [8,15]U[24,31]U[39, 47] for instruction in CCM (c - 16*floor(c/16)) in [8,15]
    #if c in {3, 7, 11, ... , 47} c%4 = 3 
    model.addConstr(gp.quicksum((taskset[i].size_i*int(c in c_instr_ccm)* x_c[i,c]+
                                taskset[i].size_ro *int(c in c_ro_ccm)* x_c[i,c])
                                for c in range(48)
                                for i in range(n)) <= taskset.ccm_size)
    #SRAM size constraint 
    #we can have input data or ro data 
    #if c in {2, 6, 10,..., 46} c%4 = 2
    model.addConstr(gp.quicksum(taskset[i].size_ro * int(c in c_ro_ram) * x_c[i,c]
                                #+ taskset[i].size_d * x_d[i,1]
                                for c in range(48)
                                for i in range(n)) <= taskset.ram_size)
    
    
    #utilization less than 1 
    model.addConstr(gp.quicksum((taskset[i].perf2[c][0]/taskset[i].period)*x_c[i,c] 
                for c in range (48)
                for i in range (n)
                ) <= 1 )

    #minimize the energy
    model.setObjective(
    gp.quicksum((taskset[i].perf2[c][1]/taskset[i].period)*x_c[i,c]
                for c in range (48)
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
    sol = []
    vals = model.getVars()
    for i in range(n*48) : 
        if round(vals[i].X,0) == 1.0 : 
            task_number = floor(i/48)
            config = i - task_number*48
            sol.append(config)
    #print(sol)
    f_str = ["24", "48", "72"]
    c_str = ["code Flash", "code CCM"]
    d_str = ["no Idata", "data ram"]
    ro_str = ["no ro", "ro FLASH", "ro RAM", "ro CCM"]

    f_ccm = {}
    f_flash = {}

    U_tot = 0
    E_tot = 0
    E_ref = 0
    s = 0
    s2 = 0
    count = 0
    ccm_used = 0
    flash_used = 0
    ram_used = 0
    nb_instr_ccm = 0
    nb_instr_flash = 0
    l_config = []
    for i in range (n) : 
        config = 0
        for c in range (48) : 
            if x_c_sol[i,c] > 0.5 : 
                if c == 0 : 
                    print(taskset[i].name, taskset[i].perf2[c])
                config = c
                '''f_i = floor(c/16)
                t = c-16*f_i
                
                c_i = floor((t)/8)
                t = t - 8*c_i
                
                d_i = floor((t)/4)
                t = t - 4 * d_i
                
                ro_i = floor((t)/1)'''
                
        #if code in flash 
        f_i = floor(config/16)
        if config in c_instr_flash : 
            flash_used += taskset[i].size_i
            nb_instr_flash += 1
            if f_str[f_i]+"f" in f_flash : 
                f_flash[f_str[f_i]+"f"] += 1
            else : 
                f_flash[f_str[f_i]+"f"] = 1
        #if code in CCM
        elif config in c_instr_ccm: 
            ccm_used += taskset[i].size_i
            nb_instr_ccm += 1 
            if f_str[f_i]+"c" in f_ccm : 
                f_ccm[f_str[f_i]+"c"] += 1
            else : 
                f_ccm[f_str[f_i]+"c"] = 1
        #ro configuration
        if config in c_ro_flash: 
            flash_used += taskset[i].size_ro
        elif config in c_ro_ram : 
            ram_used += taskset[i].size_ro
        elif config in c_ro_ccm :
            
            ccm_used += taskset[i].size_ro


            
        #print(taskset[i].name," : ", f_str[f]," | ",c_str[c]," | ", d_str[d]," | ",ro_str[ro])
        #in the case where an unexistant config is taken 
        l_config.append(config)
        util = taskset[i].perf2[config][0]/taskset[i].period
        
        energy = taskset[i].perf2[config][1]

        U_tot += util
        E_tot += energy/taskset[i].period
        E_ref += taskset[i].ref_energy/taskset[i].period
        
    if round(U_tot,0) > 1  : 
        print(l_config)
        print(sol)
        print(U_tot)
        raise Exception("problem in utilization computing")
    for i in range(len(l_config)) : 
        if l_config[i] != sol[i] : 
            raise Exception("problem in config list")

    flash_ratio = flash_used/taskset.flash_size
    ram_ratio =  ram_used/taskset.ram_size
    ccm_ratio = ccm_used/taskset.ccm_size

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
    #res = [U_gain, E_gain, flash_ratio, ram_ratio, ccm_ratio]+list(f_ccm.values())+list(f_flash.values())
    res = [U_gain, E_gain]+f_values
    f_exists = os.path.exists('results/stm32f/{}.csv'.format(n))
    with open('results/stm32f/{}.csv'.format(n), 'a') as file:
        w = writer(file,delimiter="\t" )
        if not f_exists : 
           # w.writerow(["U_gain", "E_gain", "flash_ratio", "ram_ratio", "ccm_ratio"]+list(f_ccm.keys())+list(f_flash.keys()))
           w.writerow(["U_gain", "E_gain"]+f_keys)
        w.writerow(res)
    return run_time
    
    
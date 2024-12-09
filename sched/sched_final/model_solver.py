
import gurobipy as gp
from gurobipy import GRB

from multiprocessing import Pool
from csv import writer
import os
import time
from math import floor

options = {
    "WLSACCESSID": "f2eaae29-373a-45b6-b23d-1281071a3b6a",
    "WLSSECRET": "f21d49ad-83a6-4b89-a9c7-20effb9374f8",
    "LICENSEID": 2594578,
}

def solve_32f(taskset) : 
    start_time = time.perf_counter()
    n = len(taskset)
    
    env = gp.Env(params=options)
    model = gp.Model("ilp_ram_allocator", env = env)
    model.setParam('OutputFlag', 0)
    model.setParam('TimeLimit', 3600)
    model.setParam('Threads', 1)

    conf = taskset.configurations
    nc = len(conf)
    #indexs for each memory allocations 
    c_instr_flash = [i for i in range(nc) if "NORMAL" in conf[i]]
    c_ro_flash = [i for i in range(nc) if "ro_FLASH" in conf[i]]

    c_instr_ccm = [i for i in range(nc) if "code_CCM" in conf[i]]
    c_ro_ccm = [i for i in range(nc) if "ro_CCM" in conf[i]]

    c_instr_ram = [i for i in range(nc) if "code_RAM" in conf[i]]
    c_ro_ram = [i for i in range(nc) if "ro_RAM" in conf[i]]
    c_data_ram = [i for i in range(nc) if "data_RAM" in conf[i]]

    c_no_data = [i for i in range(nc) if "no_data" in conf[i]]
    c_no_ro = [i for i in range(nc) if "no_ro" in conf[i]]

    x_c = model.addVars(n,nc, vtype = GRB.BINARY)

    #var dimension 
    #no multiple allocation
    model.addConstrs(gp.quicksum(x_c[i,j] for j in range(nc)) == 1 for i in range(n))

    #FLASH size constraint
    #we can have instructions or ro data
    model.addConstr(gp.quicksum((taskset[i].size_i * int(c in c_instr_flash) * x_c[i,c] + 
                                taskset[i].size_ro * int(c in c_ro_flash) * x_c[i,c]) 
                                for c in range(nc)  
                                for i in range(n)) <= taskset.flash_size)
    #CCM size constraint
    #we can have instruction or ro data
    model.addConstr(gp.quicksum((taskset[i].size_i*int(c in c_instr_ccm)* x_c[i,c]+
                                taskset[i].size_ro *int(c in c_ro_ccm)* x_c[i,c])
                                for c in range(nc)
                                for i in range(n)) <= taskset.ccm_size)
    #SRAM size constraint 
    #we can have input data or ro data or instructions 
    model.addConstr(gp.quicksum((taskset[i].size_ro * int(c in c_ro_ram) * x_c[i,c]+
                                taskset[i].size_i*int(c in c_instr_ram)* x_c[i,c])
                                #+ taskset[i].size_d * x_d[i,1]
                                for c in range(nc)
                                for i in range(n)) <= taskset.ram_size)
    
    
    #utilization less than 1 
    model.addConstr(gp.quicksum((taskset[i].data2[c][1]/taskset[i].period)*x_c[i,c] 
                for c in range (nc)
                for i in range (n)
                ) <= 1 )

    #minimize the energy
    model.setObjective(
    gp.quicksum((taskset[i].data2[c][2]/taskset[i].period)*x_c[i,c]
                for c in range (nc)
                for i in range (n))
    ,
    GRB.MINIMIZE)
    end_time = time.perf_counter()
    create_time = end_time - start_time 

    start_time = time.perf_counter()
    model.optimize()
    end_time = time.perf_counter()
    run_time = end_time - start_time
    return model 

def solve_32g(taskset) : 
    conf = taskset.configurations
    n = len(taskset)
    nc = len(conf)
    start_time = time.perf_counter()

    env = gp.Env(params=options)
    model = gp.Model("ilp_ram_allocator", env = env)
    model.setParam('OutputFlag', 0)
    model.setParam('TimeLimit', 3600)
    model.setParam('Threads', 1)

    x_c = model.addVars(n,nc, vtype = GRB.BINARY)

    #indexs for each memory allocations 
    c_instr_flash = [i for i in range(nc) if "NORMAL" in conf[i]]
    c_ro_flash = [i for i in range(nc) if "ro_FLASH" in conf[i]]

    c_instr_ccm = [i for i in range(nc) if "code_CCM" in conf[i]]
    c_ro_ccm = [i for i in range(nc) if "ro_CCM" in conf[i]]

    c_instr_ram1 = [i for i in range(nc) if "code_RAM." in conf[i]]
    c_ro_ram1 = [i for i in range(nc) if "ro_RAM." in conf[i]]
    c_data_ram1 = [i for i in range(nc) if "data_RAM." in conf[i]]

    c_instr_ram2 = [i for i in range(nc) if "code_RAM2." in conf[i]]
    c_ro_ram2 = [i for i in range(nc) if "ro_RAM2." in conf[i]]
    c_data_ram2 = [i for i in range(nc) if "data_RAM2." in conf[i]]

    c_no_data = [i for i in range(nc) if "no_data" in conf[i]]
    c_no_ro = [i for i in range(nc) if "no_ro" in conf[i]]

    #var dimension 
    #no multiple allocation
    model.addConstrs(gp.quicksum(x_c[i,c] for c in range(nc) )== 1 for i in range(n))

    #FLASH size constraint
    #we can have instruction or ro data
    c_f_size = gp.quicksum((taskset[i].size_i * int(c in c_instr_flash) * x_c[i,c] + 
                                taskset[i].size_ro * int(c in c_ro_flash) * x_c[i,c]) 
                                for c in range(nc)  
                                for i in range(n))
    model.addConstr(c_f_size <= taskset.flash_size)

    #CCM size constraint
    #we can have instruction or ro data
    c_ccm_size = gp.quicksum((taskset[i].size_i*int(c in c_instr_ccm)* x_c[i,c]+
                                taskset[i].size_ro *int(c in c_ro_ccm)* x_c[i,c])
                                for c in range(nc)
                                for i in range(n))
    model.addConstr(c_ccm_size <= taskset.ccm_size)

    #SRAM size constraint 
    #we can have input data, code or ro data 
    c_ram_size = gp.quicksum((taskset[i].size_ro * int(c in c_ro_ram1) * x_c[i,c]
                                + taskset[i].size_i * int(c in c_instr_ram1) * x_c[i,1])
                                for c in range(nc)
                                for i in range(n))
    model.addConstr(c_ram_size <= taskset.ram_size)
    
    #SRAM2 size constraint 
    #we can have input data, code or ro data 
    c_ram2_size = gp.quicksum((taskset[i].size_ro * int(c in c_ro_ram2) * x_c[i,c]
                            + taskset[i].size_i * int(c in c_instr_ram2) * x_c[i,1])
                            for c in range(nc)
                            for i in range(n))
    model.addConstr(c_ram2_size <= taskset.ram2_size)
    
    #utilization less than 1 
    c_u_tot = gp.quicksum((taskset[i].data2[c][1]/taskset[i].period)*x_c[i,c] 
                for c in range (nc)
                for i in range (n)
                )
    model.addConstr(c_u_tot <= 1)

    #minimize the energy
    obj_energy =gp.quicksum((taskset[i].data2[c][2]/taskset[i].period)*x_c[i,c]
                for c in range (nc)
                for i in range (n))
    model.setObjective(obj_energy, GRB.MINIMIZE)

    end_time = time.perf_counter()
    create_time = end_time - start_time 

    start_time = time.perf_counter()
    model.optimize()
    end_time = time.perf_counter()
    run_time = end_time - start_time 
    model_results = {"f_occ" : c_f_size.getValue(), 
               "ccm_occ" : c_ccm_size.getValue(),
               "ram_occ" : c_ram_size.getValue(), 
               "ram2_occ" : c_ram2_size.getValue(),
               "u_tot" : c_u_tot.getValue(), 
               "energy" : obj_energy.getValue()}
    return (model, model_results) 

def solver(taskset, proc) : 

    conf = taskset.configurations
    n = len(taskset)
    nc = len(conf)

    
    if proc == "32g" : 
        (model, model_results) = solve_32g(taskset)
    else : 
        (model, model_results) = solve_32f(taskset)


    infeasible = False 
    if model.Status == GRB.INF_OR_UNBD:
        raise Exception('Model is infeasible or unbounded')
    elif model.Status == GRB.INFEASIBLE:
        infeasible = True
    elif model.Status == GRB.UNBOUNDED:
        raise Exception('Model is unbounded')
    if not infeasible : 
        sol = []
        vals = model.getVars()

        for i in range(n*nc) : 
            if round(vals[i].X,0) == 1.0 : 
                task_number = floor(i/nc)
                config = i - task_number*nc
                sol.append(config)
        
        raw_data = []
        u_tot_out = 0
        size_i_tot = 0
        size_ro_tot = 0 
        size_d_tot = 0
        for i in range(len(sol)) :
            task = taskset[i]
            c = sol[i]
            raw_data.append((task.name,c, conf[c], task.data2[c][1], task.data2[c][2], task.period))
            u_tot_out += task.data2[c][1]/task.period
            size_i_tot += task.size_i
            size_ro_tot += task.size_ro 
            size_d_tot += task.size_d
        model_results["energy_init"] = taskset.energy
        return(raw_data, model_results)
    else :
        return("INFEASIBLE", "INFEASIBLE")

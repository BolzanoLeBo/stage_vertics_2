
import gurobipy as gp
from gurobipy import GRB

from multiprocessing import Pool
from csv import writer
import os
import time
from math import floor
def solver(taskset) : 
    conf = taskset.configurations
    n = len(taskset)
    nc = len(conf)
    start_time = time.perf_counter()

    model = gp.Model("ilp_ram_allocator")
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
    #we can have input data, code or ro data 
    model.addConstr(gp.quicksum((taskset[i].size_ro * int(c in c_ro_ram1) * x_c[i,c]
                                + taskset[i].size_i * int(c in c_instr_ram1) * x_c[i,1])
                                for c in range(nc)
                                for i in range(n)) <= taskset.ram_size)
    
    #SRAM2 size constraint 
    #we can have input data, code or ro data 
    model.addConstr(gp.quicksum((taskset[i].size_ro * int(c in c_ro_ram2) * x_c[i,c]
                            + taskset[i].size_i * int(c in c_instr_ram2) * x_c[i,1])
                            for c in range(nc)
                            for i in range(n)) <= taskset.ram2_size)
    
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
    for i in range(n*nc) : 
        if round(vals[i].X,0) == 1.0 : 
            task_number = floor(i/nc)
            config = i - task_number*nc
            sol.append(config)
    print(sol)
    for i in range(len(sol)) :
        task = taskset[i]
        c = sol[i]
        print(task.name, conf[c], task.data2[c][1], task.data2[c][2] )


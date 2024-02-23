import model_32f as mf
import model_32g as mg

from gen_taskset import *

import numpy as np
import copy
import os 
from multiprocessing import Pool

data_g = gen_dictionnary("32g")
data_f = gen_dictionnary("32f")

size_flash = 256000
size_ram = 20000
size_ram2 = 20000
size_ccm = 8000
proc = "32g"

def create_log_file(test_type, test_name):
    dirname  = "model_results/"
    if not os.path.exists(dirname):
        os.makedirs(dirname)
    dirname = dirname + "/" + test_type
    if not os.path.exists(dirname):
        os.makedirs(dirname)
    filename = str(test_name) 
    filename = dirname + "/" + filename + ".log"

    return open(filename,"w")


def run_test(n_tasks, u_tot, size_flash, size_ram, size_ram2, size_ccm, proc):
    
    test_name  = f"{proc}_{n_tasks}_{u_tot}_{size_flash}_{size_ram}_{size_ram}_{size_ram2}_{size_ccm}_"
    if proc == "32g" : 
        taskset = gen_taskset(n_tasks, u_tot, data_g[0], data_g[1], proc, size_flash, size_ram, size_ccm, size_ram2)
        return [mg.solver(taskset), test_name]
    else : 
        taskset = gen_taskset(n_tasks, u_tot, data_f[0], data_f[1], proc, size_flash, size_ram, size_ccm, size_ram2)
        return [mf.solver(taskset), test_name] 
        
        
def test_loop(task_min, task_max, step_task, u_min, u_max, step_u, size_flash, size_ram, size_ram2, size_ccm, proc, max_iter) :
    results = {}
    for n in np.arrane(task_min, task_max+1, step_task) : 
        for u in  np.arrange(u_min, u_max+1, step_u) : 
            for i in range(max_iter) : 
                [test_name, solver_res] = run_test(n, u, size_flash, size_ram, size_ram2, size_ccm, proc)
                results[str(i)] = {"test_name": test_name, "solver_results" : solver_res}
    return results

def test_wrapper (args):
    (task_min, task_max, step_task, u_min, u_max, step_u, max_iter) = args
    return test_loop(task_min, task_max, step_task, u_min, u_max, step_u, size_flash, size_ram, size_ram2, size_ccm, proc, max_iter)

def test_batch (max_processors, test_type, test_name, task_min, task_max, step_task, u_min, u_max, step_u, max_iter): 

    test_name = test_name + f"_n_tasks_{task_min}_{task_max}__utilization_{u_min}_{u_max}__iter_{max_processors*max_iter}"
    test_type = proc + "_" + test_type
    
    pool = Pool(processes=max_processors)
    
    test_results = pool.map(test_loop,  \
            zip([task_min]   * max_processors, \
                [task_max] * max_processors, \
                [step_task]       * max_processors, \
                [u_min]       * max_processors, \
                [u_max]          * max_processors, \
                [step_u]          * max_processors
                ))
    pool.close 
    
    log_file = create_log_file(test_type, test_name)
    for r in test_results : 
        log_file.write(f"{str(r)}\n")
    log_file.close()
    
    
def main() : 
    n_tasks = 10
    u_tot = 1 
    
    run_test(n_tasks,u_tot, data_g[0], data_g[1],proc, size_flash, size_ram, size_ccm, size_ram2, 1) 

main()


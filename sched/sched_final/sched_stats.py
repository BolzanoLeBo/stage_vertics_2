import model_solver as ms

from gen_taskset import *
from energy_heuristic import heuristic_solve

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


def run_test(n_tasks, u_tot, mem_util, size_flash, size_ram, size_ram2, size_ccm, proc):
    
    specs = [n_tasks, u_tot, mem_util, size_flash, size_ram, size_ram2, size_ccm, proc] 
    if proc == "32g" : 
        data = data_g
    else : 
        data = data_f
    
    taskset = gen_taskset(n_tasks, u_tot, mem_util, data[0], data[1], proc, size_flash, size_ram, size_ccm, size_ram2)
    
    # print_taskset(taskset)
    raw_data, model_results = ms.solver(taskset, proc)
    raw_data_heur, heur_results = heuristic_solve(taskset, proc)
    # print(model_results["energy_init"], model_results["energy"], heur_results["energy"])
    return (specs, raw_data, model_results, raw_data_heur, heur_results)

def run_test_with_measures(n_tasks, u_tot, mem_util, size_flash, size_ram, size_ram2, size_ccm, proc):
    
    specs = [n_tasks, u_tot, mem_util, size_flash, size_ram, size_ram2, size_ccm, proc] 
    if proc == "32g" : 
        data = data_g
    else : 
        data = data_f
    taskset = gen_taskset_with_measures(["FFT", "bubble_sort", "sine"],data[0], data[1],proc, size_flash, size_ram, size_ccm, size_ram2 )
    # print_taskset(taskset)
    raw_data, model_results = ms.solver(taskset, proc)
    raw_data_heur, heur_results = heuristic_solve(taskset, proc)
    print(model_results["energy"], heur_results["energy"])
    return (specs, raw_data, model_results, raw_data_heur, heur_results)
        
        
def test_loop(mem_util_min, mem_util_max, step_mem, u_min, u_max, step_u, n_tasks_min, n_tasks_max, step_n, size_flash, size_ram, size_ram2, size_ccm, proc, max_iter) :
    test_results = []
    for n in np.arange(n_tasks_min, n_tasks_max, step_n) : 
        for m in np.arange(mem_util_min, mem_util_max, step_mem) : 
            for u in  np.append(np.arange(u_min, u_max, step_u), u_max) : 
                for i in range(max_iter) : 
                    specs, raw_data, model_results, raw_data_heur, heur_results = run_test(n, u, m, size_flash, size_ram, size_ram2, size_ccm, proc)
                    test_results.append({"specs": specs, "raw_data" : raw_data, "model_results" : model_results, "raw_data_heur" : raw_data_heur, "heur_results" : heur_results})

    return test_results

def test_wrapper (args):
    (mem_util_min, mem_util_max, step_mem, u_min, u_max, step_u, n_tasks_min, n_tasks_max, step_n, max_iter) = args
    return test_loop(mem_util_min, mem_util_max, step_mem, u_min, u_max, step_u, n_tasks_min, n_tasks_max, step_n, size_flash, size_ram, size_ram2, size_ccm, proc, max_iter)

def test_batch (max_processors, test_type, file_prefix, mem_util_min, mem_util_max, step_mem, u_min, u_max, step_u, n_tasks_min, n_tasks_max, step_n, max_iter): 

    file_name = file_prefix + f"_mem_{mem_util_min}_{mem_util_max}__utilization_{u_min}_{u_max}__taksks_{n_tasks_min}_{n_tasks_max}__iter_{max_processors*max_iter}"
    test_type = proc + "_"  + "_" + test_type
    
    pool = Pool(processes=max_processors)
    
    test_results = pool.map(test_wrapper,  \
            zip([mem_util_min]  * max_processors, \
                [mem_util_max]  * max_processors, \
                [step_mem] * max_processors, \
                [u_min]     * max_processors, \
                [u_max]     * max_processors, \
                [step_u]    * max_processors, \
                [n_tasks_min]     * max_processors, \
                [n_tasks_max]     * max_processors, \
                [step_n]    * max_processors, \
                [max_iter]  * max_processors  
                ))
    pool.close 
    
    log_file_raw_model = create_log_file(test_type, "raw_"+ file_name+"_model")
    log_file_raw_heur = create_log_file(test_type, "raw_"+ file_name+"_heur")
    #p is the processor core index and i the test index
    for p in range (len(test_results)) :
        for i in range (len(test_results[p])) : 
            name = test_results[p][i]['specs']
            # linear model 
            raw_data = test_results[p][i]['raw_data']
            model_results = test_results[p][i]['model_results']

            # heuristic model
            raw_data_heur = test_results[p][i]['raw_data_heur']
            heur_results = test_results[p][i]['heur_results']

            res_model = f"{name}/{model_results}/{raw_data}"
            res_heur = f"{name}/{heur_results}/{raw_data_heur}"

            log_file_raw_model.write(f"{p}.{i}/{res_model}\n")
            log_file_raw_heur.write(f"{p}.{i}/{res_heur}\n")
    log_file_raw_model.close()
    log_file_raw_heur.close()

    # Write a readable file with the results 
    log_file_model = create_log_file(test_type, file_name+"_model")
    log_file_heur = create_log_file(test_type, file_name+"_heur")
    for log_file in [log_file_model, log_file_heur] : 
        tests_per_core = len(test_results[0])
        t = 0
        log_file.write("n_tasks\tu_tot\tu_mem\tu_tot_final\tu_mem_ccm\tu_mem_flash\tenergy\tenergy_init\tfailure_rate\n")
        while t < tests_per_core : 
            specs = test_results[0][t]['specs']
            n_tasks = specs[0]
            u_tot = specs[1]
            u_mem = specs[2]
            log_line = {
            "u_tot_final" : 0,
            "u_mem_ccm" : 0,
            "u_mem_flash" : 0,
            "energy" : 0,
            "energy_init" : 0,
            }
            nb_concluent_test = 0
            for i in range(max_iter) : 
                for p in range(max_processors) : 
                    if test_results != "INFEASIBLE" : 
                        nb_concluent_test += 1 
                        
                        res = test_results[p][i+t]["model_results"]
                        log_line["u_tot_final"] += res["u_tot"]
                        log_line["u_mem_ccm"] += (res["ccm_occ"]/size_ccm)
                        log_line["u_mem_flash"] += (res["f_occ"]/size_flash)
                        log_line["energy"] += res["energy"]
                        log_line["energy_init"] += res["energy_init"]

            t += max_iter
            log_file.write(f"{n_tasks}\t{u_tot}\t{u_mem}\t")
            for col in log_line.keys() : 
                log_line[col] = log_line[col]/nb_concluent_test
                log_file.write(f"{log_line[col]}\t")
            failure_rate = (1 - (nb_concluent_test/(max_iter*max_processors)))
            log_file.write(f"{failure_rate}\n")
        log_file.close()

    
    
def main() : 
    max_processors = 4
    test_type = "yo"
    file_prefix = 'yo'

    mem_util_min = 0.3
    mem_util_max = 0.5
    step_mem = 0.1

    u_min = 0.8
    u_max = 1 
    step_u = 0.1

    n_tasks_min = 18
    n_tasks_max = 21
    step_n = 1

    max_iter = 2

    # run_test(n_tasks, u_min, mem_util_min, size_flash, size_ram, size_ram2, size_ccm, proc)
    test_batch (max_processors, test_type, file_prefix, mem_util_min, mem_util_max, step_mem, u_min, u_max, step_u, n_tasks_min, n_tasks_max, step_n, max_iter)

if __name__ == '__main__' : 
    main()


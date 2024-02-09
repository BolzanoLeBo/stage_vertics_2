import model_32f as mf
import model_32g as mg

from gen_taskset import *

import numpy as np
import copy
import os 

def test_batch(max_processors, test_type, test_name, utilization_step, period_min, period_max, spm_min, spm_max, n, N, max_iterations, injection_factor):
    
    test_name = test_name + "_periods_" + str(period_min) + "_" + str(period_max) + "_spm_" + str(spm_min) + "_" + str(spm_max) + "_tasks_" + str(n) + "_cores_" + str(N) \
                          + "_iter_" + str(max_processors*max_iterations) + "_injection_factor_" + str(injection_factor)


    pool = Pool(processes=max_processors)
    test_results = pool.map(synthetic_test_wrapper,  \
            zip([max_iterations]   * max_processors, \
                [utilization_step] * max_processors, \
                [period_min]       * max_processors, \
                [period_max]       * max_processors, \
                [spm_min]          * max_processors, \
                [spm_max]          * max_processors, \
                [n]                * max_processors, \
                [N]                * max_processors, \
                [injection_factor] * max_processors))

    pool.close()


    results_tdma        = defaultdict(int)
    results_injection   = defaultdict(int)
    results_np          = defaultdict(int)


    test_utilizations = [ util*utilization_step for util in range(1,int(1/utilization_step) + 1) ] 

    for (schedulable_tdma,schedulable_injection,schedulable_non_preemptive) in test_results:
        for util in test_utilizations:
            results_tdma[util]      += schedulable_tdma[util]
            results_injection[util] += schedulable_injection[util]
            results_np[util]        += schedulable_non_preemptive[util]
    

    log_file  = create_log_file(test_type, test_name)
    log_file.write("U\tIDEAL\tTDMA\tINJ\n")
    for util in test_utilizations:
        np_results          = float(results_np[util])   / (max_iterations * max_processors)
        tdma_results        = float(results_tdma[util])   / (max_iterations * max_processors)
        injection_results   = float(results_injection[util])   / (max_iterations * max_processors)
        log_file.write ("%.2f\t%.3f\t%.3f\t%.3f\n" % \
            (util,np_results,tdma_results,injection_results))
    log_file.close()

def main() : 
    
    data_g = gen_dictionnary("32g")
    data_f = gen_dictionnary("32f")

    n_tasks = 10
    u_tot = 1 
    size_flash = 256000
    size_ram = 20000
    size_ram2 = 20000
    size_ccm = 8000
    proc = "32g"
    taskset = gen_taskset(n_tasks,u_tot, data_g[0], data_g[1],proc, size_flash, size_ram, size_ccm, size_ram2) 
    mg.solver(taskset)

main()
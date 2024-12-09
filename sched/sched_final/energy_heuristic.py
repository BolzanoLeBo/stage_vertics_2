
from gen_taskset import *

import numpy as np
import copy
import os 

def test_schedulable(tab_task): 
    u_tot = 0
    for task_dict in tab_task :
        task = task_dict['task']
        imp = task_dict['imp']
        conf = task_dict['c']
        u_tot += task.data2[conf][1]/task.period
    return True if u_tot <= 1 else False

def get_current_u_tot(tab_task) : 
    u_tot = 0
    for task_dict in tab_task :
        task = task_dict['task']
        imp = task_dict['imp']
        conf = task_dict['c']
        u_tot += task.data2[conf][1]/task.period
    return u_tot 

def get_current_e_tot(tab_task) : 
    e_tot = 0
    for task_dict in tab_task :
        task = task_dict['task']
        imp = task_dict['imp']
        conf = task_dict['c']
        e_tot += task.data2[conf][2]/task.period
    return e_tot 

def get_current_u_tot_with_variation(tab_task, change_index, dict_changed ) : 
    tab_task2 = tab_task.copy()
    tab_task2[change_index] = dict_changed
    u_tot = 0
    for task_dict in tab_task2 :
        task = task_dict['task']
        imp = task_dict['imp']
        conf = task_dict['c']
        u_tot += task.data2[conf][1]/task.period
    # print(f"{dict_changed['task'].name} : {get_current_u_tot(tab_task)} / {u_tot}")
    return u_tot 

def get_conf(taskset, task, freq, code_mem) : 
    if task.data_conf == "only_i" : 
        conf = taskset.configurations.index(f"data_RAM.no_ro.{code_mem}.{freq}")
    elif task.data_conf == "only_ro" : 
        conf = taskset.configurations.index(f"no_data.ro_FLASH.{code_mem}.{freq}")
    else : 
        conf = taskset.configurations.index(f"data_RAM.ro_FLASH.{code_mem}.{freq}")
    return conf

def print_tab_task(taskset, tab_task) : 
    for task in tab_task : 
        print(f"{task['task'].name} : {taskset.configurations[task['c']]} / {task['task'].data2[task['c']][1]- task['task'].ref_energy} " )

def heuristic_solve(taskset, proc) : 
    # print(taskset.configurations)
    tab_task = []
    for task in taskset : 
        if proc == "32g" :
            conf_ccm = get_conf(taskset, task, 150, "code_CCM")
            conf_flash = get_conf(taskset, task, 150, "NORMAL")
        else : 
            conf_ccm = get_conf(taskset, task, 72, "code_CCM")
            conf_flash = get_conf(taskset, task, 72, "NORMAL")

        if task.ref_energy == 0:
            # Handle the error gracefully
            print(task.name)
            print_taskset(taskset)
            print(f"Warning: ref_energy is zero for task: {task}")  
            ccm_improve = 0 
        else :           
            ccm_improve = (task.ref_energy - task.data2[conf_ccm][2])/task.ref_energy
        tab_task.append({'task': task, 'imp': ccm_improve, 'c': conf_flash, 'opt' : False})
    tab_task.sort(key = lambda x: x['imp'], reverse = True)
    i = 0
    current_ccm = 0
    size_ccm = taskset.ccm_size
    while i < len(tab_task) and test_schedulable(tab_task) and (current_ccm < size_ccm) : 
        task = tab_task[i]['task']

        if tab_task[i]['imp'] > 0 and ((current_ccm + task.size_i) < size_ccm): 
            current_ccm += task.size_i
            if proc == "32g" :
                tab_task[i]['c'] = get_conf(taskset, task, 170, "code_CCM")
            else : 
                tab_task[i]['c'] = get_conf(taskset, task, 72, "code_CCM")
            tab_task[i]['opt'] = True
        i += 1
    # print(f"i : {i} / sched : {get_current_u_tot(tab_task)} / ccm {current_ccm < size_ccm}")  

    i = 0
    while i < len(tab_task) and test_schedulable(tab_task) : 
        task = tab_task[i]['task']

        if tab_task[i]['opt'] == False :
            dict_changed = tab_task[i].copy()
            if proc == '32g' : 
                conf = get_conf(taskset, task, '26_RANGE2', 'NORMAL')
                dict_changed['c'] = conf
            else : 
                conf = get_conf(taskset, task, 24, 'NORMAL')
                dict_changed['c'] = conf

            if get_current_u_tot_with_variation(tab_task, i, dict_changed) <= 1 and task.data2[dict_changed['c']][2] < task.data2[tab_task[i]['c']][2]  : 

                tab_task[i]['c'] = conf
                tab_task[i]['opt'] = True
        i += 1 
    
    # print(f"i : {i} / sched : {get_current_u_tot(tab_task)}" )
    raw_data = []
    # print_tab_task(taskset, tab_task)
    for task_dict in tab_task : 
        task = task_dict['task']
        conf = task_dict['c']
        raw_data.append((task.name, conf, taskset.configurations[conf], task.data2[conf][1], task.data2[conf][2], task.period))

    heur_results = {"f_occ" : 0, 
               "ccm_occ" : current_ccm,
               "ram_occ" : 0, 
               "ram2_occ" : 0,
               "u_tot" : get_current_u_tot(tab_task), 
               "energy" : get_current_e_tot(tab_task), 
               "energy_init" : taskset.energy}
    if test_schedulable(tab_task) == False : 
        return ("INFESEABILE", "INFEASIBLE")
    else : 
        return(raw_data, heur_results)


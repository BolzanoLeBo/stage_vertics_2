import csv
from glob import glob
import pandas as pd
from random import randint
import numpy as np
from drs import drs
import copy
import os
from schedcat.model.tasks import SporadicTask, TaskSystem


    #sample the runtimes
MAX    = 2000000000
size_i = {
        'FFT':1000,
        'rsa_enc':145, 
        'rsa_dec':172, 
        'bubble_sort':1280, 
        'bubble_sort_no_opt':1280,
        'dijkstra':532,
        'mat_mul':198,
        'pointer_chase':62,
        'recursion':116,
        'sine':228
    }

size_d = {
        'FFT':4000,
        'rsa_enc':500, 
        'rsa_dec':4000, 
        'bubble_sort':3910, 
        'bubble_sort_no_opt':3910,
        'dijkstra':6250,
        'mat_mul':4680,
        'pointer_chase':0,
        'recursion':8,
        'sine':0
    }


size_ro = {
        'FFT':0,
        'rsa_enc':0, 
        'rsa_dec':0, 
        'bubble_sort':0, 
        'bubble_sort_no_opt':0,
        'dijkstra':0,
        'mat_mul':0,
        'pointer_chase':3910,
        'recursion':0,
        'sine':6840
    }
freqs = ["16_RANGE2", "26_RANGE2", "16", "26", "30", "60", "90", "120", "150", "170", "150_BOOST", "170_BOOST"]
only_idata_codes = ['FFT','rsa_enc', 'rsa_dec', 'bubble_sort', 'bubble_sort_no_opt','dijkstra','mat_mul', 'recursion']
only_ro_codes = ['pointer_chase']

def get_csv_line(f, lname) : 
    reader = csv.reader(f, delimiter="\t")
    for line in reader :
        if lname in line : 
            return(line)
        
def flatten_dict(dictionary):
    flat_list = []

    def flatten_helper(d, parent_key=""):
        for key, value in d.items():
            new_key = f"{parent_key}.{key}" if parent_key else key
            if isinstance(value, dict):
                flatten_helper(value, new_key)
            else:
                flat_list.append((new_key, value[0], value[1]))

    flatten_helper(dictionary)
    return flat_list

def gen_dictionnary(loc):
    bench_list = (os.listdir(loc))

    if loc == "32g" :
        f_order = ["16_no_PLL", "16_RANGE2", "26_RANGE2", "16", "26", "30", "60", "90", "120", "150", "170", "150_BOOST", "170_BOOST"]
        data_order = ["data_RAM", "data_RAM2", "no_data"]
        code_order = ["NORMAL", "code_CCM", "code_RAM", "code_RAM2"]
        ro_order = ["no_ro", "ro_FLASH", "ro_RAM", "ro_CCM", "ro_RAM2", "CACHE_OFF-PRE_OFF", "CACHE_OFF-PRE_ON", "CACHE_ON-PRE_ON"]
    else :
        f_order = ["8_no_PLL","16","24","48","72"]
        data_order = ["data_RAM", "no_data"]
        code_order = ["NORMAL", "code_CCM", "code_RAM"]
        ro_order = ["ro_FLASH", "ro_RAM", "ro_CCM","no_ro"] 

    #initialize the dictionnary 
    dico_f = {}
    for f in f_order : 
        dico_f[f] = [MAX, MAX] #wcet and energy
    
    dico_c = {}
    for c in code_order : 
        dico_c[c] = copy.deepcopy(dico_f)
    
    dico_ro = {}
    for ro in ro_order : 
        dico_ro[ro] = copy.deepcopy(dico_c)

    dico_d = {}
    for d in data_order : 
        dico_d[d] = copy.deepcopy(dico_ro)

    data_bench = {}
    for bench in bench_list : 
        data_bench[bench] = copy.deepcopy(dico_d)
    for bench in bench_list : 
        data_list = os.listdir("{}/{}/{}".format(loc,bench,"results"))
        #for one benchmark check which configurations are used 
        common_data = [[data, data_o] for data in data_list for data_o in data_order if data_o+"_" in data]
        #data is the name in the repository and data_o is the name in the dictionnary 
        #if there is at least on used configuration 
        if common_data != [] : 
            for idata in common_data :
                code_list = os.listdir("{}/{}/{}/{}".format(loc,bench,"results",idata[0]))
                common_code = [code for code in code_list for code_o in code_order if code_o == code]
                #if there is no read only
                if "ro" not in idata[0] :
                    #get the used code configurations 
                    for icode in common_code : 
                        with open ("{}/{}/{}/{}/{}/summary.csv".format(loc,bench,"results",idata[0], icode)) as f :
                            i = 1
                            wcet = get_csv_line(f,"maxD")
                            energies = get_csv_line(f, "avrgE")
                            for freq in f_order :  
                                data_bench[bench][idata[1]]["no_ro"][icode][freq][0] = float(wcet[i])
                                data_bench[bench][idata[1]]["no_ro"][icode][freq][1] = float(energies[i])
                                i+=1


                else : 
                    #there is data and read only at the same time
                    common_ro = [[ro,ro_o] for ro in data_list for ro_o in ro_order if ro_o+"_" in ro]
                    for iro in common_ro :
                        for icode in common_code : 
                            with open ("{}/{}/{}/{}/{}/summary.csv".format(loc,bench,"results",iro[0], icode)) as f :
                                i = 1
                                wcet = get_csv_line(f,"maxD")
                                energies = get_csv_line(f, "avrgE")
                                for freq in f_order :  
                                    data_bench[bench][idata[1]][iro[1]][icode][freq][0] = float(wcet[i])
                                    data_bench[bench][idata[1]][iro[1]][icode][freq][1] = float(energies[i])
                                    i+=1

        else :
            #there is no input data
            common_ro = [[ro,ro_o] for ro in data_list for ro_o in ro_order if ro_o+"_" in ro]
            for iro in common_ro :
                for icode in common_code : 
                    with open ("{}/{}/{}/{}/{}/summary.csv".format(loc,bench,"results",iro[0], icode)) as f :
                        i = 1
                        wcet = get_csv_line(f,"maxD")
                        energies = get_csv_line(f, "avrgE")
                        for freq in f_order :  
                            data_bench[bench]["no_data"][iro[1]][icode][freq][0] = float(wcet[i])
                            data_bench[bench]["no_data"][iro[1]][icode][freq][1] = float(energies[i])
                            i+=1
    flat_data = {}
    for k in data_bench.keys() :
        flat_data[k] = list(flatten_dict(data_bench[k]))
    return [flat_data, data_bench]


def gen_taskset(nb_tasks, util, mem_util, flat_data, data_bench, proc, size_flash, size_ram, size_ccm, size_ram2 = 0):
    #make random utilization 
    utils = drs(nb_tasks, util)
    #create the taskset
    taskset = TaskSystem()
    taskset.configurations = [c[0] for c in flat_data['FFT']]
    data_size = 0
    #find the periods
    Tmin = 10000
    Tmax = 100000
    gran = 10000
    periods = (np.random.randint(Tmin/gran, Tmax/gran, size=nb_tasks)*gran).tolist()
    
    ref_runtimes = [int(periods[i]*utils[i]) for i in range(len(utils))]
    u_tot = np.sum(np.divide(ref_runtimes,periods))
    taskset.u_tot = u_tot 
    #total size of read only to calculate the space left for instructions 
    ro_total = 0
    for i in range (nb_tasks) : 
        #choose a random benchmark for the task
        
        task_name = np.random.choice(list(flat_data.keys()))
                #ref runtime is the reference runtime it is how normally the code is executed
        if proc == "32g" : 
            if task_name in only_idata_codes : 
                bench_runtime = data_bench[task_name]["data_RAM"]["no_ro"]["NORMAL"]["150"][0]
                bench_energy = data_bench[task_name]["data_RAM"]["no_ro"]["NORMAL"]["150"][1]
            elif task_name in only_ro_codes : 
                bench_runtime =  data_bench[task_name]["no_data"]["ro_FLASH"]["NORMAL"]["150"][0]
                bench_energy = data_bench[task_name]["no_data"]["ro_FLASH"]["NORMAL"]["150"][1]
            else : 
                bench_runtime =  data_bench[task_name]["data_RAM"]["ro_FLASH"]["NORMAL"]["150"][0]
                bench_energy = data_bench[task_name]["data_RAM"]["ro_FLASH"]["NORMAL"]["150"][1]

        elif proc == "32f" : 
            if task_name in only_idata_codes : 
                bench_energy = data_bench[task_name]["data_RAM"]["no_ro"]["NORMAL"]["72"][1]
                bench_runtime = data_bench[task_name]["data_RAM"]["no_ro"]["NORMAL"]["72"][0]
            elif task_name in only_ro_codes : 
                bench_runtime =  data_bench[task_name]["no_data"]["ro_FLASH"]["NORMAL"]["72"][0]
                bench_energy = data_bench[task_name]["no_data"]["ro_FLASH"]["NORMAL"]["72"][1]
            else : 
                bench_runtime =  data_bench[task_name]["data_RAM"]["ro_FLASH"]["NORMAL"]["72"][0]
                bench_energy = data_bench[task_name]["data_RAM"]["ro_FLASH"]["NORMAL"]["72"][1]
        
        #runtime and energy with the adjusted utilization
        ref_runtime = ref_runtimes[i]
        ref_energy = ref_runtime*bench_energy/bench_runtime

        #the scale between the measured runtime and the calculated runtime 
        scale_runtime = ref_runtime/bench_runtime

        #create the task
        task = SporadicTask(ref_runtime, periods[i])
        #task parameters (for the optimization algo)
        task.ref_runtime = ref_runtime
        task.bench_runtime = bench_runtime
        task.ref_energy = ref_energy
        task.bench_energy = bench_energy
        task.name = task_name

        #choose the size of the tasks 
        
        if task_name not in only_ro_codes : 
            task.size_d = randint(min(size_d.values()), max(size_d.values()))
        else :
            task.size_d = 0
        if task_name not in only_idata_codes : 
            task.size_ro = randint(min(size_ro.values()), max(size_ro.values()))
            ro_total += task.size_ro
        else : 
            task.size_ro = 0

        
        
        flat_data2 = []
        for c in range (len(flat_data[task_name])) :
            runtime1 = flat_data[task_name][c][1]
            energy1 = flat_data[task_name][c][2]
            if runtime1 != MAX : 
                #Harmonize the runtime and energy with the period 
                runtime2 =  int(runtime1*scale_runtime)
                energy2 = int(energy1*runtime2/runtime1)
                flat_data2.append((flat_data[task_name][0], int(runtime2), energy2))          
            else: 
                flat_data2.append((flat_data[task_name][0], MAX, MAX))   

        task.data1 = flat_data[task_name]
        task.data2 = flat_data2       
        taskset.append(task)
        data_size += size_d[task_name]
    
    #compute the instruction memory utilization 
    flash_left = (size_flash * mem_util) - ro_total
    task_mem_ratio = drs(nb_tasks, 1)
    for i in range (nb_tasks) : 
        task = taskset[i]
        task.size_i = int(flash_left * task_mem_ratio[i])

    energy_total = 0
    for task in taskset : 
        energy_total += task.ref_energy/task.period
        

    taskset.assign_ids_by_deadline()
    taskset.sort_by_deadline()
    #set storage size 
    taskset.ram_size = size_ram#40000
    taskset.ram2_size = size_ram2
    taskset.ccm_size = size_ccm #8000
    taskset.flash_size = size_flash #256000

    taskset.energy = energy_total
    return(taskset)

def print_taskset(taskset) : 
    for task in taskset : 
        print(f"\n -------- \n {task.name}")
        print(f"T : {task.period}")
        print(f"runtime : {task.bench_runtime}/{task.ref_runtime}")
        print(f"energy : {task.bench_energy}/{task.ref_energy}\n")
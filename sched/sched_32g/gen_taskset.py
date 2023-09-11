import csv
from glob import glob
import pandas as pd
from random import randint
import numpy as np
from drs import drs
import copy
from schedcat.model.tasks import SporadicTask, TaskSystem


    #sample the runtimes
MAX    = 2000000000
size_i = {
        'FFT':1000,
        'RSA_enc':145, 
        'RSA_dec':172, 
        'bubble_sort':1280, 
        'bubble_sort_no_opt':1280,
        'dijkstra':532,
        'kalman':1620,
        'mat_mul':198,
        'pointer_chase':62,
        'recursif':116,
        'sine':228
    }

size_d = {
        'FFT':4000,
        'RSA_enc':500, 
        'RSA_dec':4000, 
        'bubble_sort':3910, 
        'bubble_sort_no_opt':3910,
        'dijkstra':6250,
        'kalman':4000,
        'mat_mul':4680,
        'pointer_chase':0,
        'recursif':8,
        'sine':0
    }


size_ro = {
        'FFT':0,
        'RSA_enc':0, 
        'RSA_dec':0, 
        'bubble_sort':0, 
        'bubble_sort_no_opt':0,
        'dijkstra':0,
        'kalman':0,
        'mat_mul':0,
        'pointer_chase':3910,
        'recursif':0,
        'sine':6840
    }
freqs = ["16_RANGE2", "26_RANGE2", "16", "26", "30", "60", "90", "120", "150", "170", "150_BOOST", "170_BOOST"]
only_idata_codes = ['FFT','RSA_enc', 'RSA_dec', 'bubble_sort', 'bubble_sort_no_opt','dijkstra','kalman','mat_mul', 'recursif']
only_ro_codes = ['pointer_chase', 'sine']
    
benchs = ['FFT',
        'RSA_enc', 
        'RSA_dec', 
        'bubble_sort', 
        'bubble_sort_no_opt',
        'dijkstra',
        'kalman',
        'mat_mul',
        'pointer_chase',
        'recursif',
        'sine']

def gen_dictionnary(loc):   
    
    '''nb_tasks = int(sys.argv[1])
    util = int(sys.argv[2])'''


    dico_bench = {'FFT':[MAX,MAX],
                'RSA_enc':[MAX,MAX], 
                'RSA_dec':[MAX,MAX], 
                'bubble_sort':[MAX,MAX], 
                'bubble_sort_no_opt':[MAX,MAX],
                'dijkstra':[MAX,MAX],
                'kalman':[MAX,MAX],
                'mat_mul':[MAX,MAX],
                'pointer_chase':[MAX,MAX],
                'recursif':[MAX,MAX],
                'sine':[MAX,MAX]}
    
    dico_ro = {"no_ro" :copy.deepcopy(dico_bench), "ro_f" :copy.deepcopy(dico_bench),
                "ro_r" : copy.deepcopy(dico_bench), "ro_c" : copy.deepcopy(dico_bench)}
    dico_pre = {"pre_on":copy.deepcopy(dico_ro), "pre_off" : copy.deepcopy(dico_ro)}
    dico_cache = {"cache_on":copy.deepcopy(dico_pre), "cache_off":copy.deepcopy(dico_pre)}
    dico_instr = {"cf":copy.deepcopy(dico_cache), "cc" : copy.deepcopy(dico_cache)}
    dico_f = {}
    for f in freqs : 
        dico_f[f] = copy.deepcopy(dico_instr)

    #exemple : 
    # dico_f["150_BOOST"]["cc"]["cache_on"]["pre_off"]["ro_f"]["FFT"][0] 
    # => runtime of bench FFT at 150 MHz in boost mode when code is in ccm, ro in flash, cache enable and prefetch disable
    # => if there is no tests with ro it will be MAX in the dictionnary and not used

    #append the non read only codes data
    files = glob(loc+"/*.csv")
    for file in files : 
        with open(file, 'r') as f : 
            reader = csv.DictReader(f, delimiter = '\t')
            found = 1

            name = file.removeprefix(loc+"\\")
            #select which data type we use
            if "runtime" in name : 
                unit = 0
            elif "energy" in name : 
                unit = 1
            else : 
                found = 0

            #select what executions we extract data from

            if "CODE_CCM" in name : 
                code = 'cc'
            else : 
                code = "cf"

            if "ro_FLASH" in name : 
                ro = "ro_f"
            elif "ro_RAM" in name : 
                ro = "ro_r"
            elif "ro_CCM" in name : 
                ro = "ro_c"
            else : 
                ro = "no_ro"

            pre = "undef"
            if "PRE_ON" in name : 
                pre = "pre_on"
            else : 
                for n in ["NORMAL", "CODE_CCM", "CODE_CCM-CACHE_OFF", "PRE_OFF"] : 
                    if n in name :
                        
                        pre = "pre_off"
                if pre == "undef" : 
                    found = 0

            cache = "undef"
            if "CACHE_OFF" in name : 
                cache = "cache_off"
            else : 
                for n in ["NORMAL", "CODE_CCM","CACHE_ON"] : 
                    if n in name: 
                        #print(name)             
                        cache = "cache_on"
                if cache == "undef" : 
                    found = 0
            for col in reader :
                bench_name = col["group"]
                for f in freqs : 
                    #update the corresponding dictionnary at the good place
                    #it can occurs that ro only are in the other data we don't want to add this
                    if found and bench_name in benchs : 
                        dico_f[f][code][cache][pre][ro][bench_name][unit] = float(col[f])

    return(dico_f)

    #----------------------------GENERATE TASK SET--------------------------------------------
def gen_taskset(nb_tasks, util, dico_f, size_flash, size_ram, size_ccm):
    #make random utilization 
    utils = drs(nb_tasks, util)
    #create the taskset
    taskset = TaskSystem()
    data_size = 0
    #find the periods
    Tmin = 10000
    Tmax = 100000
    gran = 10000
    periods = (np.random.randint(Tmin/gran, Tmax/gran, size=nb_tasks)*gran).tolist()
    
    ref_runtimes = [int(periods[i]*utils[i]) for i in range(len(utils))]
    u_tot = np.sum(np.divide(ref_runtimes,periods))
    taskset.u_tot = u_tot 
    '''print(u_tot)
    print("periods ", periods)
    print("utiks", utils)
    print("runtimes", ref_runtimes)'''
    for i in range (nb_tasks) : 

        #choose a random benchmark for the task
        
        task_name = np.random.choice(benchs)
        task_id = benchs.index(task_name)
       #print(task_name, task_id)


        #ref runtime is the reference runtime it is how normally the code is executed
        if task_name in only_idata_codes : 
            bench_runtime = dico_f["150"]["cf"]["cache_on"]["pre_off"]["no_ro"][task_name][0]
            bench_energy = dico_f["150"]["cf"]["cache_on"]["pre_off"]["no_ro"][task_name][1]
        else : 
            bench_runtime = dico_f["150"]["cf"]["cache_on"]["pre_off"]["ro_f"][task_name][0]
            bench_energy = dico_f["150"]["cf"]["cache_on"]["pre_off"]["ro_f"][task_name][1]
        
        ref_runtime = ref_runtimes[i]
        ref_energy = ref_runtime*bench_energy/bench_runtime
        scale_runtime = ref_runtime/bench_runtime
        #create the task
        task = SporadicTask(ref_runtime, periods[i])
        #task parameters (for the optimization algo)
        task.ref_runtime = ref_runtime
        task.ref_energy = ref_energy
        task.name = task_name

        '''task.size_i = size_i[task_name]
        task.size_d = size_d[task_name]
        task.size_ro = size_ro[task_name]'''
        task.size_i = randint(min(size_i.values()), max(size_i.values()))
        if task_name not in only_ro_codes : 
            task.size_d = randint(min(size_d.values()), max(size_d.values()))
        else :
            task.size_d = 0
        if task_name not in only_idata_codes : 
            task.size_ro = randint(min(size_ro.values()), max(size_ro.values()))
        else : 
            task.size_ro = 0


        c_index = ["cf", "cc"]
        pre_index = ["pre_on", "pre_off"]
        cache_index = ["cache_on", "cache_off"]
        ro_index = ["no_ro", "ro_f", "ro_r", "ro_c"]
        
        #init all the tasks info
        perf = []
        perf2 = []
        for f in range (len(freqs)) : 
            perf.append([])
            for c in range (len(c_index)) :
                perf[f].append([]) 
                for prec in range (4) : 
                    perf[f][c].append([])      
                    #prec 
                    # 0             1           2           3
                    # cache_on  cache_on    cache_off   cache_off 
                    # pre_on    pre_off     pre_on      pre_off
                             
                    for ro in range (len(ro_index)):
                        [runtime1,energy1] = dico_f[freqs[f]][c_index[c]][cache_index[prec>1]][pre_index[prec%2]][ro_index[ro]][task_name]
                        if runtime1 != MAX : 
                            #Harmonize the runtime and energy with the period 
                            runtime2 =  int(runtime1*scale_runtime)
                            energy2 = int(energy1*runtime2/runtime1)
                            perf[f][c][prec].append([runtime2,energy2])  
                            perf2.append([runtime2,energy2])  
                        else: 
                            perf[f][c][prec].append([MAX,MAX])      
                            perf2.append([MAX, MAX])                
        task.perf = perf
        task.perf2 = perf2
        taskset.append(task)
        data_size += size_d[task.name]

    taskset.assign_ids_by_deadline()
    taskset.sort_by_deadline()
    #set storage size 
    taskset.ram_size = size_ram#40000
    taskset.ccm_size = size_ccm #8000
    taskset.flash_size = size_flash #256000
    #print the runtime and the period
    #print(taskset)
    #print(data_size)
    #print(taskset[0].name, taskset[0].perf[3][0][0][0])
    return(taskset)

#dico = gen_dictionnary("./bench")
#gen_taskset(8, 1, dico, 256000, 40000, 8000)
#print(dico["150_BOOST"]["cc"]["cache_off"]["pre_on"]["no_ro"]["recursif"][0])
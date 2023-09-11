from sched_32f import model_32f2 as mf


from sched_32g import model_32g2 as mg


from average_results import average_results

from sched_32g import gen_taskset as gg
from sched_32f import gen_taskset as gf
import numpy as np
import copy
import os 

def main() : 
    
    dicog = gg.gen_dictionnary("./sched_32g/bench")
    dicof = gf.gen_dictionnary("./sched_32f/bench")
    proc_test = 'g'
    Ntests = 1
    nb_tasks = [8,16,32,64,128]

    times = []
    for ni in nb_tasks :
        n = str(ni) 
        time = 0
        for i in range(Ntests):
            if proc_test == 'g' :
                taskset = gg.gen_taskset(ni,1, dicog, 256000, 40000, 8000) 
                time += mg.solver(taskset)

            else : 
                taskset = gf.gen_taskset(ni,1, dicof, 256000, 40000, 8000) 
                time += mf.solver(taskset)

            if i*100/Ntests%10 == 0 : 
                os.system('cls')
                print(n, " tasks :", int(i*100/Ntests),"%") 
        times.append(time/Ntests)
    if proc_test == 'g' : 
        average_results("./results/stm32g","./output/out_stm32g.csv")
    elif proc_test == 'f' : 
        average_results("./results/stm32f","./output/out_stm32f.csv")
    print("running average times (s):", times)

main()
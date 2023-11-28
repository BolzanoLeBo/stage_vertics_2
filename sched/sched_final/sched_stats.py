import model_32f as mf
import model_32g as mg

from gen_taskset import *

import numpy as np
import copy
import os 

def main() : 
    
    data_g = gen_dictionnary("32g")
    data_f = gen_dictionnary("32f")

    n_tasks = 50
    u_tot = 1 
    size_flash = 256000
    size_ram = 40000
    size_ccm = 8000
    proc = "32f"
    taskset = gen_taskset(n_tasks,u_tot, data_f[0], data_f[1],proc, size_flash, size_ram, size_ccm) 
    mf.solver(taskset)

main()
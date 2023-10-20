
import os

import pandas as pd
import numpy as np

def main() : 
    
    with open("param_tabl.txt", 'r') as f : 
        lines = f.readlines()
    proc = lines[0].removesuffix("\n")
    code_cmp = lines[1].removesuffix("\n").split('/')
    data_cmp = lines[2].removesuffix("\n").split('/')
    
    col = (lines[3].removesuffix("\n")).split()
    name = lines[4].removesuffix("\n")
    if len(lines) > 5 : 
        option = lines[5].removesuffix("\n")
    else : 
        option = 0
    os.mkdir("res_table/{}/final/{}".format(proc,name))
    for unity in ['duration', 'energy', 'intensity', 'worst_case'] : 
        if option == "all" : 
            path_ref = "res_table/{}/{}-{}-{}_all.csv".format(proc,code_cmp[0], data_cmp[0],unity)
            path_cmp = "res_table/{}/{}-{}-{}_all.csv".format(proc,code_cmp[1], data_cmp[1],unity)
            if os.path.exists(path_ref) == False:
                print("{} not found, creation of the csv".format(path_ref))
                os.system("python create_tab.py {} {} {} {} ro".format(code_cmp[0], data_cmp[0],unity, proc))
            if os.path.exists(path_cmp) == False :
                print("{} not found, creation of the csv".format(path_cmp))
                os.system("python create_tab.py {} {} {} {} ro".format(code_cmp[1], data_cmp[1],unity, proc))
        elif option == "ro" : 
            ro_cmp = data_cmp
            path_ref = "res_table/{}/{}-data_RAM-{}-{}.csv".format(proc,code_cmp[0], ro_cmp[0],unity)
            path_cmp = "res_table/{}/{}-data_RAM-{}-{}.csv".format(proc,code_cmp[1], ro_cmp[1],unity)
            if os.path.exists(path_ref) == False:
                print("{} not found, creation of the csv".format(path_ref))
                os.system("python create_tab.py {} data_RAM {} {} {}".format(code_cmp[0], unity, proc, ro_cmp[0]))
            if os.path.exists(path_cmp) == False :
                print("{} not found, creation of the csv".format(path_cmp))
                os.system("python create_tab.py {} data_RAM {} {} {}".format(code_cmp[1], unity, proc, ro_cmp[1]))
        else :  
            path_ref = "res_table/{}/{}-{}-{}.csv".format(proc,code_cmp[0], data_cmp[0],unity)
            path_cmp = "res_table/{}/{}-{}-{}.csv".format(proc,code_cmp[1], data_cmp[1],unity)
            if os.path.exists(path_ref) == False:
                print("{} not found, creation of the csv".format(path_ref))
                os.system("python create_tab.py {} {} {} {}".format(code_cmp[0], data_cmp[0],unity, proc))
            if os.path.exists(path_cmp) == False :
                print("{} not found, creation of the csv".format(path_cmp))
                os.system("python create_tab.py {} {} {} {}".format(code_cmp[1], data_cmp[1],unity, proc))
        

        df_ref = pd.read_csv(path_ref, sep='\t')
        df_cmp = pd.read_csv(path_cmp, sep='\t')
        ref_dico = {}
        cmp_dico = {}
        for c in col+['group'] : 
            ref_dico[c] = df_ref[c].to_list()
            cmp_dico[c] = df_cmp[c].to_list()

        data_final = []
        for i in range (0,len(df_ref.index)) : 
            ref_val = np.array([ref_dico[c][i] for c in col])
            cmp_val = np.array([cmp_dico[c][i] for c in col])
            delta = [(round((ref_val[j] - cmp_val[j])/ref_val[j], 3)) for j in range (len(ref_val))]
            data_final.append(delta)
        rows =list(ref_dico['group'])
        
        df_final = pd.DataFrame(data_final, index = rows, columns=col)
        df_final.index.name = 'group'
        df_final.to_csv("res_table/"+proc+'/'+'final'+'/' + name + '/'+ name + '-' + unity + ".csv", sep='\t')
    os.system("cp ./param_tabl.txt res_table/{}/final/{}".format(proc,name))
main()
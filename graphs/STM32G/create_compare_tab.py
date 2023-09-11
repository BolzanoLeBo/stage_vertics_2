import csv
import glob
import os
import sys
import pandas as pd
import numpy as np
import openpyxl
import xlsxwriter
def main() : 
    
    with open("param_tabl.txt", 'r') as f : 
        lines = f.readlines()
    ro = False
    reference = lines[0].removesuffix("\n")
    data_to_cmp = lines[1].removesuffix("\n")
    unity = lines[2].removesuffix("\n")
    col = (lines[3].removesuffix("\n")).split()
    name = lines[4].removesuffix("\n")
    if len(lines) > 5 : 
        option = lines[5].removesuffix("\n")
    else : 
        option = 0

    
    if option == "ro" : 
        path_ref = "res_table/{}_{}_all.csv".format(reference,unity)
        path_cmp = "res_table/{}_{}_all.csv".format(data_to_cmp,unity)
        if os.path.exists(path_ref) == False:
            print("{} not found, creation of the csv".format(path_ref))
            os.system("python create_tab.py {} {} ro".format(reference,unity))
        if os.path.exists(path_cmp) == False :
            print("{} not found, creation of the csv".format(path_cmp))
            os.system("python create_tab.py {} {} ro".format(data_to_cmp,unity))
    else :  
        path_ref = "res_table/{}_{}.csv".format(reference,unity)
        path_cmp = "res_table/{}_{}.csv".format(data_to_cmp,unity)
        if os.path.exists(path_ref) == False:
            print("{} not found, creation of the csv".format(path_ref))
            os.system("python create_tab.py {} {}".format(reference,unity))
        if os.path.exists(path_cmp) == False :
            print("{} not found, creation of the csv".format(path_cmp))
            os.system("python create_tab.py {} {}".format(data_to_cmp,unity))



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
    df_final.to_csv("res_table/" + name + ".csv", sep='\t')
main()
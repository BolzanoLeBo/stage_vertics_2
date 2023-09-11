import csv
import glob
import os
import sys
import pandas as pd
import numpy as np
import openpyxl
import xlsxwriter
def main() : 
    col = ['24MHz', '48MHz', '72MHz']
    name = sys.argv[1]
    with open("param_tabl.txt", 'r') as f : 
        lines = f.readlines()
    reference = lines[0].removesuffix("\n")
    data_to_cmp = lines[1].removesuffix("\n")
    unity = lines[2].removesuffix("\n")
    path_ref = "res_table/{}_{}.csv".format(reference,unity)
    path_cmp = "res_table/{}_{}.csv".format(data_to_cmp,unity)
    if os.path.exists(path_ref) == False:
        print("{} not found, creation of the csv".format(path_ref))
        os.system("python create_tab.py {} {}".format(reference,unity))
    if os.path.exists(path_cmp) == False :
        print("{} not found, creation of the csv".format(path_cmp))
        os.system("python create_tab.py {} {}".format(data_to_cmp,unity))

    df_ref = pd.read_csv(path_ref, sep='\t').astype({'24MHz':'float', '48MHz':'float','72MHz':'float'})
    df_cmp = pd.read_csv(path_cmp, sep='\t').astype({'24MHz':'float', '48MHz':'float','72MHz':'float'})
    
    data_final = []

    for i in range (0,len(df_ref.index)) :
         ref_val = np.array((df_ref.iloc[i].values)[1:len(df_ref.iloc[i])])
         cmp_val = np.array((df_cmp.iloc[i].values)[1:len(df_cmp.iloc[i])])
         delta = [(round((ref_val[j] - cmp_val[j])/ref_val[j], 3)) for j in range (len(ref_val))]
         data_final.append(delta)
    rows =df_ref['group'].tolist()
    cols = df_ref.columns[1:len(df_ref.columns)].to_list()
    df_final = pd.DataFrame(data_final, index = rows, columns=cols)
    df_final.index.name = 'group'
    df_final.to_csv("res_table/" + name + ".csv", sep='\t')
main()
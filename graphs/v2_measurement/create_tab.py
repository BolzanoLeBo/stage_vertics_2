import csv
import glob
import os
import sys
import pandas as pd
import numpy as np
def extract_line(path, unity) : 
    unity_dico = {"intensity" : "avrgI", "energy" : "avrgE", "duration" : "avrgD", "worst_case" : "maxD"}
    with open(path, 'r') as ref : 
        
        reader = csv.reader(ref, delimiter = '\t')
        line_ret = []
        f_check = 0
        f = []
        for line in reader: 
            if not f_check : 
                #get the frequency line
                f = line[1:len(line)]
                f_check = 1 
            if len(line) > 0 : 
                if line[0] == unity_dico[unity] : 
                    line_ret = line[1:len(line)]
        return [line_ret, f]
            
            
def main() : 
    code_config = sys.argv[1]
    data_config = sys.argv[2]
    #energy intensity duration
    unity = sys.argv[3]
    proc = sys.argv[4]
    freqs = []
    ro_config = 0

    list_dir = os.popen("ls -d {}/*/".format(proc)).read().split()

    for i in range (len(list_dir)) : 
        list_dir[i] = list_dir[i].removesuffix("/")
    tab_val = []
    tab_name = []
    if len(sys.argv) > 5 and sys.argv[5] == "ro": 
        #ro_except is for when you want to compare all the codes 
        #it will add ro code into the tabs even if there is no input data
        ro_except = 1
    elif len(sys.argv) > 5 and sys.argv[5] != "ro" :
        ro_except = 0
        ro_config = sys.argv[5]
    else :
        ro_except = 0

    #for all directories
    for dir in list_dir : 
        print("write the line of ", dir)
        #check the file 
        files = os.popen("ls -r {}/ ".format(dir)).read().split()
        
        if 'results' in files : 
            path = dir + '/results/'
            files2 = os.popen("ls -r {}/ ".format(path)).read().split()
            data_found = 0 
            data_file = ""
            for f in files2 : 
                if data_found == 0 : 
                    if ro_config == 0 and data_config in f : 
                        if "ro_FLASH" in f or "ro" not in f : 
                            #if we want to compare input data only, 
                            #if there is a case with both read only and input then the case with ro in flas will be taken
                            data_file = f
                            data_found = 1
                    elif ro_config != 0 and (ro_config in f) : 
                        if "data_" not in f :
                            print("found a only read only case")
                            data_file = f
                            data_found = 1
                        elif data_config+'_'+ro_config in f : 
                            print("found a both read only and input data case")
                            data_file = f
                            data_found = 1

            if data_found : 
                #add the benchmark test
                tab_name.append(dir.removeprefix(proc+'/')) 
                final_path = path+data_file + '/' +code_config+'/summary.csv'
                res = extract_line(final_path, unity)
                freqs = res[1]
                tab_val.append(res[0])

            #special cases 
            else : 
                print("file not detected, try exceptions")
                #codes with only ro data and no input data
                ro_code = [proc+'/''sine', proc+'/''pointer_chase']
                if dir in ro_code and ro_except: 
                    print("ro exception")
                    for f in files2 : 
                        if "ro_FLASH" in f : 
                            data_file = f
                            data_found = 1
                    path_ro = path + data_file + '/' +code_config+'/summary.csv'
                    if os.path.exists(path_ro) :
                            tab_name.append(dir.removeprefix(proc+'/'))
                            res = extract_line(path_ro, unity)
                            freqs = res[1]
                            tab_val.append(res[0])
                            
                else : 
                    print("no exception found")   
    
    df = pd.DataFrame(tab_val, index = tab_name, columns = freqs)
    df.index.name = 'group'
    print('create csv file')
    if not ro_except : 
        if ro_config == 0 : 
            df.to_csv('res_table/'+proc+'/'+code_config+'-'+data_config+'-'+unity+'.csv', sep='\t')
        else : 
            df.to_csv('res_table/'+proc+'/'+code_config+'-'+data_config+'-'+ro_config+'-'+unity+'.csv', sep='\t')
    elif ro_except and ro_config == 0: 
        df.to_csv('res_table/'+proc+'/'+code_config+'-'+data_config+'-'+unity+'_all'+'.csv', sep='\t')




        

main()
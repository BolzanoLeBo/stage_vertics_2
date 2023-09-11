import csv
import glob
import os
import sys
import pandas as pd
import numpy as np
def extract_line(path, unity) : 
    with open(path, 'r') as ref : 
        reader = csv.reader(ref, delimiter = '\t')
        for line in reader: 
            if line[0] == unity : 
                return line[1:len(line)]
            
def main() : 
    freq = ["16_RANGE2", "26_RANGE2", "16", "26", "30", "60", "90", "120", "150", "170", "150_BOOST", "170_BOOST"]
    name = sys.argv[1]
    print(name)
    #energy intensity duration
    unity = sys.argv[2]
    list_dir = os.popen("ls -d */").read().split()

    for i in range (len(list_dir)) : 
        list_dir[i] = list_dir[i].removesuffix("/")
    tab_val = []
    tab_name = []
    if len(sys.argv) > 3 and sys.argv[3] == "ro": 
        ro_except = 1
    else :
        ro_except = 0

    #for all directories
    for dir in list_dir : 
        print("write the line of ", dir)
        #check the file 
        path = dir+'/'+ name+'.csv'
        if os.path.exists(path) :
            
            #add the benchmark test
            tab_name.append(dir) 
            
            tab_val.append(extract_line(path, unity))

        #special cases 
        else : 
            print("file not detected, try exceptions")
            #codes with only ro data and no input data
            ro_code = ['sine', 'pointer_chase']
            
            if dir in ro_code and ro_except: 
                print("ro exception")
                path_ro = dir+ '/'+'ro_FLASH-' + name+ '.csv'
                if os.path.exists(path_ro) :
                        tab_name.append(dir)
                        tab_val.append(extract_line(path_ro, unity))
            else : 
                print("no exception found")              
    df = pd.DataFrame(tab_val, index = tab_name, columns = freq)
    df.index.name = 'group'
    print('create csv file')
    if not ro_except : 
        df.to_csv('res_table/'+name+'_'+unity+'.csv', sep='\t')
    else : 
        df.to_csv('res_table/'+name+'_'+unity+'_all'+'.csv', sep='\t')



        

main()
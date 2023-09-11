from csv import writer,reader
from os import listdir
import numpy as np
import copy
def average_results(input_loc, output_loc) : 


    key_init = 0
    files = [f for f in listdir(input_loc)]
    nb_tasks = [int(f.removesuffix(".csv")) for f in files]
    nb_tasks.sort()
    data = {}
    for n in nb_tasks : 
        f = str(n)+'.csv'
        init = 0
        csv_tab = open(input_loc+'/'+f, 'r')
        r = reader(csv_tab, delimiter ="\t")
        nb_value = 0
        keys = []
        #read the csv file
        for line in r :
            if line != [] and line != ['\n']: 
                nb_value += 1
                #if the data dictionnary is not initialized with the csv name 
                if not init : 
                    #take the first row of the csv file 
                    keys = line 
                    for key in keys : 
                        #initiate the keys
                        if not key_init : 
                            data[key] = {}
                        data[key][n] = 0
                    key_init = 1
                    init = 1
                else : 
                    #add the values at the corresponding location
                    for i in range (len(line)) : 
                        
                        data[keys[i]][n]+=float(line[i])
                
        for key in keys : 
            #compute the average
            data[key][n] = data[key][n]/(nb_value-1)

    #create/open the output files
    out_file = open(output_loc, 'w')
    out_round = open((output_loc.removesuffix(".csv"))+"_round.csv", 'w')
    w = writer(out_file,delimiter="\t" )
    wr = writer(out_round,delimiter="\t" )


    #remove the full of zeros categories in the dictionarry 
    zeros = [0.0 for f in files]
    data_round = copy.deepcopy(data)
    for key in list(data.keys()) : 
        line = []
        line_round = []
        for n in data[key].keys(): 
            val = float(data[key][n])
            line.append(val)
            line_round.append(round(val,2))
        if line == zeros : 
            data.pop(key)
        if line_round == zeros : 
            data_round.pop(key)

    w.writerow(['nb_tasks'] + list(data.keys()))
    wr.writerow(['nb_tasks'] + list(data_round.keys()))
    #write the csv files
    for n in nb_tasks : 
        line = []
        line_round = []
        for key in list(data.keys()) : 
            val = float(data[key][n])
            line.append(val)
        for key in list(data_round.keys()) : 
            val = float(data[key][n])
            line_round.append(round(val,2))

        w.writerow([n] + line)
        wr.writerow([n] + line_round)


    




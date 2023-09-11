import csv
from fileinput import filename
import glob
from logging import config
import os
from pickle import FALSE
import sys
import pandas as pd
import numpy as np
import json
import openpyxl
import xlsxwriter

#unzip the stpm file and return the intensity pics data 
def create_tabs(file_name, rep_name, sampling_f, i_treshold, t_treshold) : 

	data_i = []
	data_t = []
	time_stamp = []
	src_path = "./{}/{}".format(rep_name,file_name)
	dst_path = "./{}/p".format(rep_name)
	os.system("cp {} {}".format(src_path, dst_path))
	#unzip the graph and create the result file
	print("unzip " + file_name)
	os.system('unzip {}/p/{} -d {}/p'.format(rep_name, file_name, rep_name))

	#With a high  sampling frequency there is several graph files made 
	nb_file = os.popen('ls {}/p| wc -l'.format(rep_name)).read()
		
	start_pic = 0

	run_i = 0
	run_count = 0

	t1 = 0
	t2 = 0
	#reading the graph files 
	for i in range (1, int(nb_file)-2) : 
		csv_name = glob.glob('{}/p/*rawfile_{}.csv'.format(rep_name, i))
		with open(csv_name[0], 'r') as file : 
			line_index = 0
			reader = csv.reader(file ,  delimiter = ';',quoting=csv.QUOTE_NONE)
			for line in reader :
				line_index+=1
				#to gain execution time we can emulate another sampling frequency and process less data
				if line_index%(50000//sampling_f) == 0 : 
					i = float(line[1])
					t = float(line[0])
					#detect pic starting
					if i > i_treshold and not start_pic: 
						run_i = 0
						run_count = 0
						start_pic = 1 
						#take the starting time
						t1 = t
					#detect pic ending
					elif i < i_treshold and start_pic: 
						start_pic = 0 
						#take end time
						t2 = t
						#check if the pic can be considered like a processing pic
						if (t2-t1)/1000 > t_treshold: 
							data_i.append(run_i/run_count)
							data_t.append(round((t2-t1)/1000, 5))
							time_stamp.append((t1, t2))
						t1 = 0
						t2 = 0
					#sum the intensity during the pic to caluclate the average
					if start_pic : 
						run_i += i
						run_count += 1 
	os.system("rm -r ./{}/p/*".format(rep_name))
	return (data_i, data_t, time_stamp)

#with the data pics create dictionaries files by parsing the different execution configurations 
def get_current(data_i, data_t,param_col, nb_ex, proc) : 
	row = ['intensity', 'runtime', 'energy']
	lines = []
	with open('./{}.txt'.format(param_col)) as f:
		for l in f : 
			lines.append(l.replace('\n', ''))
		nb_f = int(lines[0])
		nb_config = int(lines[2])
		#extract the frequencies and the execution types 
		f = lines[1].split(' ')
		if len(f) != nb_f: 
			print("wrong number of frequency")
			print(f)
			exit() 
		config = lines[3].split(' ')
		if len(config) != nb_config:
			print("wrong number of execution types")
			print(config)
			exit()

		#remove the reset pic and add the data in the dataframe 
		if len(data_i)%nb_config!= 0 : 
			print("remove the reset pic")
			intensity_tab = data_i[1:len(data_i)]
			duration_tab = data_t[1:len(data_i)]
		else : 
			intensity_tab = data_i
			duration_tab = data_t

		if len(intensity_tab) != nb_ex*nb_f*nb_config : 
			print(len(intensity_tab)," measures instead of ", nb_ex*nb_f*nb_config )
			exit()
		res_dic = {}
		df = []
		#split the different executions and create dictionaries for each ones 
		for c in range(nb_config) : 
		
			res_dic[config[c]] = {}
			
			for i in range(len(f)) : 
				start = i*nb_config*nb_ex + c*nb_ex
				end = start + nb_ex
				res_dic[config[c]][f[i]] = {"i" : {"val":[], "max": 0, "min" : 0, "avrg":0}, 
											"d":{"val":[], "max": 0, "min" : 0, "avrg":0}, 
											"e" : {"val":[], "max": 0, "min" : 0, "avrg":0}}
				res_dic[config[c]][f[i]]["i"]["val"] = intensity_tab[start : end]
				res_dic[config[c]][f[i]]["i"]["max"] = np.max( [intensity_tab[start : end]])
				res_dic[config[c]][f[i]]["i"]["min"] = np.min( [intensity_tab[start : end]])
				res_dic[config[c]][f[i]]["i"]["avrg"] = np.mean( [intensity_tab[start : end]])

				res_dic[config[c]][f[i]]["d"]["val"] = duration_tab[start : end]
				res_dic[config[c]][f[i]]["d"]["max"] = np.max( [duration_tab[start : end]])
				res_dic[config[c]][f[i]]["d"]["min"] = np.min( [duration_tab[start : end]])
				res_dic[config[c]][f[i]]["d"]["avrg"] = np.mean( [duration_tab[start : end]])
				
				for k in range (len(res_dic[config[c]][f[i]]["d"]["val"])) : 
					#in 32g if there is special dunamic voltage scaling, to calculate energy we have to take it into account
					if proc == "32g" : 
						if "RANGE2" in f[i] or "no_PLL" in f[i]:
							res_dic[config[c]][f[i]]["e"]["val"].append(1.0 * res_dic[config[c]][f[i]]["d"]["val"][k] * res_dic[config[c]][f[i]]["i"]["val"][k])
						elif "BOOST" in f[i] : 
							res_dic[config[c]][f[i]]["e"]["val"].append(1.28 *res_dic[config[c]][f[i]]["d"]["val"][k] * res_dic[config[c]][f[i]]["i"]["val"][k])
						else : 
							res_dic[config[c]][f[i]]["e"]["val"].append(1.2 * res_dic[config[c]][f[i]]["d"]["val"][k] * res_dic[config[c]][f[i]]["i"]["val"][k])
					else : 
						res_dic[config[c]][f[i]]["e"]["val"].append(3 * res_dic[config[c]][f[i]]["d"]["val"][k] * res_dic[config[c]][f[i]]["i"]["val"][k])
				res_dic[config[c]][f[i]]["e"]["max"] = np.max( res_dic[config[c]][f[i]]["e"]["val"])
				res_dic[config[c]][f[i]]["e"]["min"] = np.min( res_dic[config[c]][f[i]]["e"]["val"])
				res_dic[config[c]][f[i]]["e"]["avrg"] = np.mean( res_dic[config[c]][f[i]]["e"]["val"])
			
	return (res_dic)

#with the dictionary create csv file to use it later 
def create_csv(dico, loc, name) : 

	print(loc, name)
	os.system("cd {}results && mkdir {}".format(loc,name))
	
	for c in dico.keys() : 
		freqs = list(dico[c].keys())
		os.system("cd {}results/{} && mkdir {}".format(loc,name, c))
		
		#for each configuration we create one file for each unit (time, intensity and energy) with each executions
		file_i = open("{}results/{}/{}/intensity.csv".format(loc,name, c), "w")
		file_d = open("{}results/{}/{}/runtime.csv".format(loc,name, c), "w")
		file_e = open("{}results/{}/{}/energy.csv".format(loc,name, c), "w")
		#we also create a summary file with important informations (avrg, max, min)
		file_s = open("{}results/{}/{}/summary.csv".format(loc,name, c), "w")

		w_i = csv.writer(file_i, delimiter = "\t")
		w_d = csv.writer(file_d, delimiter = "\t")
		w_e = csv.writer(file_e, delimiter = "\t")
		w_s = csv.writer(file_s, delimiter = "\t")

		w_i.writerow(freqs)
		w_d.writerow(freqs)
		w_e.writerow(freqs)
		w_s.writerow(["unit"]+freqs)

		for u in ["i", "d", "e"] : 
			for m in ["min", "max", "avrg"] : 
				row = [m+u.upper()]
				for f in freqs : 
					row.append(dico[c][f][u][m])
				w_s.writerow(row)
		for i in range(len(dico[c][freqs[0]]["i"]["val"])) : 
			for u in ["i", "d", "e"] : 
				row = []
				for f in freqs : 
					row.append(dico[c][f][u]["val"][i])
				if u == "i" : 
					w_i.writerow(row)
				elif u == "d" : 
					w_d.writerow(row)
				else : 
					w_e.writerow(row)
		



def main() : 


	#take arguments (graph, run treshold and sleep treshhold)	
	rep_name = sys.argv[1]
	param_col = sys.argv[2]
	nb_ex = int(sys.argv[3])
	if len(sys.argv) > 4 : 
		i_treshold = float(sys.argv[4])
		t_treshold = float(sys.argv[5])
	else :
		i_treshold = 2000
		t_treshold = 0.001
	intensity = []
	time = []
	graph = []
	if ("32f" in rep_name) : 
		proc = "32f"
	elif ("32g" in rep_name) : 
		proc = "32g"
	else : 
		print("wrong filename")
		exit()
	print("get {} measures".format(rep_name))
	#Copy the graphs into the processing directory
	file_list = os.listdir(rep_name)
	
	if "intensity.json" not in file_list or "time.json" not in file_list: 
		os.system("cd {} && mkdir p".format(rep_name))
		for f in file_list:
			if f[-5:len(f)] == ".stpm" :
				#get the number of execution on each config 
				graph.append(f)
				tab = create_tabs(f, rep_name, 50000,i_treshold, t_treshold)
				intensity.append(tab[0])
				time.append(tab[1])
		os.system('cd {} && rmdir p'.format(rep_name))	
		
		
		
		
		with open(rep_name+"/intensity.json", 'w') as f:
			# indent=2 is not needed but makes the file human-readable 
			# if the data is nested
			json.dump(intensity, f, indent=2) 

		with open(rep_name+"/time.json", 'w') as f:
			# indent=2 is not needed but makes the file human-readable 
			# if the data is nested
			json.dump(time, f, indent=2) 


	else : 
		file_list.remove("intensity.json")
		file_list.remove("time.json")
		file_list.remove("results")
		os.system("cd {} && rm -r results".format(rep_name))
		with open(rep_name+"/intensity.json", 'r') as f:
			intensity = json.load(f)

		with open(rep_name+"/time.json", 'r') as f:
			time = json.load(f)

	os.system("cd {} && mkdir results".format(rep_name))

	for i in range (len(intensity)) : 
		dico = get_current(intensity[i], time[i], param_col, nb_ex, proc)
		print(file_list[i][0:-5])
		create_csv(dico, rep_name, file_list[i][0:-5])

main()
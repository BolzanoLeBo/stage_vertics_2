import csv
import glob
import os
import sys
import pandas as pd
import numpy as np
import openpyxl
import xlsxwriter

def create_tabs(file_name, rep_name) : 

	data_i = []
	data_t = []
	src_path = "./{}/{}".format(rep_name,file_name)
	dst_path = "./{}/p".format(rep_name)
	os.system("cp {} {}".format(src_path, dst_path))
	#unzip the graph and create the result file
	os.system('unzip {}/p/{} -d {}/p'.format(rep_name, file_name, rep_name))

	#With a high  sampling frequency there is several graph files made 
	nb_file = os.popen('ls {}/p| wc -l'.format(rep_name)).read()
		#reading the graph files 
	for i in range (1, int(nb_file)-2) : 
		csv_name = glob.glob('{}/p/*rawfile_{}.csv'.format(rep_name, i))
		with open(csv_name[0], 'r') as file : 

			reader = csv.reader(file ,  delimiter = ';',quoting=csv.QUOTE_NONE)

			for line in reader :
				data_i.append(float(line[1]))
				data_t.append(float(line[0]))
	os.system("rm -r ./{}/p/*".format(rep_name))
	return (data_i, data_t)

def get_current(data_i, data_t,param_col,i_t,t_t) : 
	start_pic = 0
	end_pic = 0
	run_i = 0
	run_count = 0

	intensity_tab = []
	duration_tab = []
	time_tab = []
	t1 = 0
	t2 = 0
	i_treshold = i_t
	t_treshold = t_t
	for i in range (0,len(data_i)) : 
		
		if data_i[i] > i_treshold and not start_pic: 
			run_i = 0
			run_count = 0
			start_pic = 1 
			end_pic = 0
			t1 = data_t[i]

		elif data_i[i] < i_treshold and start_pic: 
			start_pic = 0 
			end_pic = 1
			t2 = data_t[i]
			if (t2-t1)/1000 > t_treshold: 
				intensity_tab.append(run_i/run_count)
				duration_tab.append(round((t2-t1)/1000, 5))
				time_tab.append((t1, t2))
			t1 = 0
			t2 = 0
		if start_pic : 
			run_i += data_i[i]
			run_count += 1 
	row = ['intensity', 'runtime', 'timestamp', 'energy']


	col = []
	lines = []
	with open('{}.txt'.format(param_col)) as f:
		
		for l in f : 
			lines.append(l.replace('\n', ''))
		nb_f = int(lines[0])
		nb_ex = int(lines[2])
		#extract the frequencies and the execution types 
		f = lines[1].split(' ')
		if len(f) != nb_f: 
			print("wrong number of frequency")
			print(f)
			exit() 
		ex = lines[3].split(' ')
		if len(ex) != nb_ex:
			print("wrong number of execution types")
			print(ex)
			exit()
		tab_f = []

		#fusion of the two tabs 
		'''for n in range (nb_ex):
			f2 = f.copy()
			for i in range (nb_f):
				f2[i] = f2[i] + ' ' + ex[n]
			tab_f.append(f2) '''
		#remove the reset pic and add the data in the dataframe 
		intensity_tab = intensity_tab[1:len(intensity_tab)]
		duration_tab = duration_tab[1:len(duration_tab)]
		time_tab = time_tab[1:len(time_tab)]
		tab_i = []
		tab_d = []
		tab_t = []
		df = []
		#split the different executions 
		for n in range (nb_ex): 
			tab_i = [intensity_tab[i] for i in range (len(intensity_tab)) if i % nb_ex == n]
			tab_d = [duration_tab[i] for i in range (len(duration_tab)) if i % nb_ex == n]
			tab_t = [time_tab[i] for i in range (len(time_tab)) if i % nb_ex == n]
			tab_e = []
			#print(len(tab_d))
			for i in range (len(f)) : 
				if "RANGE2" in f[i]:
					tab_e.append(1.0*tab_d[i]*tab_i[i])
				elif "BOOST" in f[i] : 
					tab_e.append(1.28*tab_d[i]*tab_i[i])
				else : 
					tab_e.append(1.2*tab_d[i]*tab_i[i])
			df.append(pd.DataFrame([tab_i, tab_d, tab_t, tab_e], index = row, columns = f))

	return (df, ex)

def main() : 


	#take arguments (graph, run treshold and sleep treshhold)	
	rep_name = sys.argv[1]
	param_col = sys.argv[2]
	if len(sys.argv) > 3 : 
		i_treshold = float(sys.argv[3])
		t_treshold = float(sys.argv[4])
	else :
		i_treshold = 2000
		t_treshold = 0.001
	#dest_name = sys.argv[2]
	#graph = sys.argv[3]
	intensity = []
	time = []
	graph = []

	#Copy the graphs into the processing directory
	file_list = os.listdir(rep_name)
	os.system("cd {} && mkdir p".format(rep_name))
	for f in file_list:
		if f[-5:len(f)] == ".stpm" : 
			graph.append(f)
			tab = create_tabs(f, rep_name)
			intensity.append(tab[0])
			time.append(tab[1])
	os.system('cd {} && rmdir p'.format(rep_name))	
	path = './{}/{}.xlsx'.format(rep_name, rep_name)

	#create the excel file 
	for i in range (len(intensity)) : 

		(df, ex) = get_current(intensity[i], time[i], param_col, i_treshold, t_treshold)
		for j in range(len(ex)) : 
			if len(intensity) == 1 :
				sheet = "{}".format(ex[j])
			else : 
				sheet = "{}-{}".format(graph[i].removesuffix(".stpm"),ex[j])
			print("creating the sheet : ", sheet)
			df[j].to_csv(rep_name+'/'+sheet+'.csv', sep='\t')
			try :
				book = openpyxl.load_workbook(path)
				book.create_sheet(sheet)
				writer = pd.ExcelWriter(path, engine='openpyxl', mode='a', if_sheet_exists="overlay")
				df[j].to_excel(writer, sheet ) 
				writer.close()
			except : 
				df[j].to_excel(path, sheet_name = sheet)


main()
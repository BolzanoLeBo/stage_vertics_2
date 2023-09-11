get_current_autom : 

transform the raw measure files (stpm) into several csv files 
parameters : input directory, parsing parameters, nb of measures for each config
optionnal : current treshold, time treshold

example : python get_current_autom.py 32f/dijkstra/ param32f 100 2000 0.001

run32g/f allow to compute all the measures with good parameters 



create_tab : 

after using get_current can go in each csv files and make a summary csv file for each benchmarks 
parameters : code configuration, input data configuration, unity to check (energy, duration, intensity, worst case), processor (32f or 32g) 
optionnal : read only configuration (type the read only config you want to get the tab or type "all" to compare read only with other benchmarks) 

examples : 
python create_tab.py code_CCM data_RAM energy 32g
-> give a tab comparing all the benchmarks with input data in RAM

python create_tab.py code_CCM data_RAM energy 32g all 
-> will add read only benchmarks to the tab even if they have no input data 
(it will choose read only in FLASH) 

python create_tab.py code_CCM data_RAM energy 32g ro_FLASH
-> will compare codes with read only data 
if the code has also input data it will take data in RAM in this case 



create_compare_tab : 
create tabs which compare two tabs of your choice. If the two tabs does not exists it will create them. 
The configurations are written in the param_tabl.txt file 
the results will be located into res_file/processor_you_choose/final

param_tabl : 
processor(32f or 32g)
code location reference / code location to compare 
data location regerence / data location to compare 
list of frequency 
name of the final directory
options (optionnal) 

options can be : 
"ro" in this case data_location (second line) should be read only 
"all" compare tabs with the "all" option



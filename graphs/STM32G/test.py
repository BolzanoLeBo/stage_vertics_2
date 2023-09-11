
lines = []
with open("param_12.txt") as f : 
    for l in f : 
        lines.append(l.replace('\n', ''))
nb_f = int(lines[0])
nb_ex = int(lines[2])
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

for n in range (nb_ex):
    f2 = f.copy()
    for i in range (nb_f):
        f2[i] = f2[i] + ' ' + ex[n]
    tab_f.append(f2) 
print(tab_f)

intensity_tab = [1,2,1,2,1,2,1,2,1,2,1,2]
tabi = []
for n in range (nb_ex): 
    tabi.append([intensity_tab[i] for i in range (len(intensity_tab)) if i % nb_ex == n])
print(tabi)


s = "zpfapofka.stpm"
print(s[-5:len(s)])
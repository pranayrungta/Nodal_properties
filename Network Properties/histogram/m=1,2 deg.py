bins = 20


source = './../../../Network Properties/data/'
fileData = [('RSF_n=100_k=1_ic=100.txt', 'm=1'),
            ('RSF_n=100_k=2_ic=100.txt', 'm=2'),]
outfile = './../../../Network Properties/probability/deg_RSF_n=100_m=1,2_ic=100'

xlabel = ('Degree', {'fontsize':18})
ylabel = ('Probablility',{'fontsize':18}) # 
title = 'RSF n=100 m=1,2 ic=100'

log = 'y' # 'x' 'y' 'xy'
output = 'png' #'show' 'eps' 'png'



import matplotlib.pyplot as plt
import numpy as np


if('x' in log):plt.xscale('log')
if('y' in log):plt.yscale('log')
plt.title(title)
plt.xlabel(*xlabel); plt.ylabel(*ylabel)

labels=[];weights=[]; data=[]
for filename,label in fileData:
    fileData = eval( open(source+filename,'r').read() )
    prop = []
    for tag,links in fileData:
        for nbrs in links.values():
            prop+=[len(nbrs)]
    prop_weights = np.ones(len(prop))/len(prop)
    
    data += [prop]
    weights += [prop_weights]
    labels += [label]

plt.hist(data, bins=bins, weights=weights, label=labels )
plt.legend()
plt.tight_layout()
if(output=='show'): plt.show()
else: plt.savefig( '%s.%s'%(outfile,output) )    

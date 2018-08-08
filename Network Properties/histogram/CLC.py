bins = 20

source = './../../../Network Properties/data/'
fileData = [('clc_RSF_n=100_k=1_ic=100.txt', 'm=1'),
            ('clc_RSF_n=100_k=2_ic=100.txt', 'm=2'),]
outfile = './../../../Network Properties/probability/clc_RSF_n=100_m=1,2_ic=100'

xlabel = ('Closeness Centrality', dict(fontsize=18) )
ylabel = ('Probablility', dict(fontsize=18) )
title = 'RSF n=100 m=1 ic=100'

log = 'y' # 'x' 'y' 'xy'
output = 'show' #'show' 'eps' 'png'




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
    for tag,links,propi in fileData:
        prop += propi.values()
    prop_weights = np.ones(len(prop))/len(prop)
    
    data += [prop]
    weights += [prop_weights]
    labels += [label]

result=plt.hist(data, bins=bins, weights=weights, label=labels )
plt.legend()
plt.tight_layout()
if(output=='show'): plt.show()
else: plt.savefig( '%s.%s'%(outfile,output) )    

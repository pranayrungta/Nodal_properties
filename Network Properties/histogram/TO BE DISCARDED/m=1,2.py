bins = 20


source = './../../../Network Properties/data/'
btc_filename = 'clc_RSF_n=100_k=1_ic=100.txt'
clc_filename = 'clc_RSF_n=100_k=2_ic=100.txt'
filename_labels = ['m=1','m=2']
outfile = './../../../Network Properties/probability/clc_RSF_n=100_m=1,2_ic=100'

xlabel = ('Closeness Centrality', dict(fontsize=18) )
ylabel = ('Probablility', dict(fontsize=18) )
title = 'RSF n=100 k=1,2 ic=100'

output = 'show' #'show' 'eps' 'png'







import matplotlib.pyplot as plt
import matplotlib as mpl; mpl.style.use('classic')
import numpy as np

plt.yscale('log')
plt.title(title)
plt.xlabel(*xlabel); plt.ylabel(*ylabel)

btc_data = eval( open(source+btc_filename,'r').read() )
btc = []
for i,(tag,links,btci) in enumerate(btc_data):
    btc+=btci.values()
btc_weights = np.ones(len(btc))/len(btc)

clc_data = eval( open(source+clc_filename,'r').read() )
clc = []
for i,(tag,links,clci) in enumerate(clc_data):
    clc+=clci.values()
clc_weights = np.ones(len(clc))/len(clc)

plt.hist([btc,clc], bins=bins, weights=[btc_weights,clc_weights],
         label=filename_labels)
plt.legend()
plt.tight_layout()
if(output=='show'): plt.show()
else: plt.savefig( '%s.%s'%(outfile,output) )    

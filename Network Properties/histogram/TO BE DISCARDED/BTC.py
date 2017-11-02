bins = 20


source = './../../../Network Properties/data/'
filename = 'btc_RSF_n=100_k=2_ic=100.txt'
outfile = './../../../Network Properties/probability/hist_'+filename[:-4]

xlabel = ('Betweeness Centrality', {'fontsize':18})
ylabel = ('Probablility',{'fontsize':18}) # 
title = ' '.join(filename[:-4].split('_'))

output = 'show' #'show' 'eps' 'png'







import matplotlib.pyplot as plt
import matplotlib as mpl; mpl.style.use('classic')
import numpy as np


data = eval( open(source+filename,'r').read() )

btc = []
for i,(tag,links,btci) in enumerate(data):
    btc+=btci.values()

plt.yscale('log')
plt.title(title)
plt.xlabel(*xlabel); plt.ylabel(*ylabel)
weights = np.ones(len(btc))/len(btc)
plt.hist(btc, bins=bins, weights=weights)
plt.tight_layout()
if(output=='show'): plt.show()
else: plt.savefig( '%s.%s'%(outfile,output) )    

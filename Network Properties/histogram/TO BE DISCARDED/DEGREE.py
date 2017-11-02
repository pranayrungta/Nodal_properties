bins = 20

source = './../../../Network Properties/data/'
filename = 'RSF_n=100_k=2_ic=100.txt'
outfile = './../../../Network Properties/probability/hist_deg_'+filename[:-4]

xlabel = ('Degree', {'fontsize':18})
ylabel = ('Probablility',{'fontsize':18}) # 
title = ' '.join(filename[:-4].split('_'))

output = 'png' #'show' 'eps' 'png'







import matplotlib.pyplot as plt
import matplotlib as mpl; mpl.style.use('classic')
import numpy as np


data = eval( open(source+filename,'r').read() )

btc = []
for i,(tag,links) in enumerate(data):
    for j,nbrs in links.iteritems():
        btc+=[len(nbrs)]

plt.yscale('log')
plt.title(title)
plt.xlabel(*xlabel); plt.ylabel(*ylabel)
weights = np.ones(len(btc))/len(btc)
plt.hist(btc, bins=bins, weights=weights)
plt.tight_layout()
if(output=='show'): plt.show()
else: plt.savefig( '%s.%s'%(outfile,output) )    

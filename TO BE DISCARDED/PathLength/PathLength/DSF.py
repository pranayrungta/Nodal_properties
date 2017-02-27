filename = './../../data_python/DSF.txt'



from results import *
from PathLength import *
execfile(filename)# 'data' variable is read


avgPathLength = dsf_result(data,pathLength)
f = open('dsf_pl.txt','w')
f.write('order\tPathLength\n')
for order,p in sorted(avgPathLength.iteritems()):
    f.write('%s\t%0.2f\n'%(order,p) )
f.close()

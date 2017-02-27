filename = './../../data_python/Ring.txt'



from results import *
from PathLength import *
execfile(filename)# 'data' variable is read


avgPathLength = ring_result(data,pathLength)
f = open('ring_pl.txt','w')
f.write('#n\tk\tPathLength\n')
for n,kp in sorted(avgPathLength.iteritems()):
    for k,p in sorted(kp.iteritems()):
        f.write('%s\t%s\t%0.2f\n'%(n,k,p) )
    f.write('\n')
f.close()

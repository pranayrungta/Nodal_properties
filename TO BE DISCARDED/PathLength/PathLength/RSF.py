filename = './../../data_python/RSF.txt'

from results import *
from PathLength import *

print 'reading data file...'
execfile(filename)# 'data' variable is read

print 'Calculating'
avgPathLength = rsf_result(data,pathLength)
print 'done'

f = open('rsf_pl.txt','w')
f.write('#n\tk\tPathLength\n')
for n,kp in sorted(avgPathLength.iteritems()):
    for k,p in sorted(kp.iteritems()):
        f.write('%s\t%s\t%0.2f\n'%(n,k,p) )
    f.write('\n')
f.close()

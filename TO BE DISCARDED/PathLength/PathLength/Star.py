filename = './../../data_python/Star.txt'



from results import *
from PathLength import *
execfile(filename)# 'data' variable is read


avgPathLength = star_result(data,pathLength)
f = open('star_pl.txt','w')
f.write('n\tPathLength\n')
for n,p in sorted(avgPathLength.iteritems()):
    f.write('%s\t%0.2f\n'%(n,p) )
f.close()

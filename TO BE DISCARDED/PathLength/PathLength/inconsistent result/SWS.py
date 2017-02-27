filename = './../../data_python/SWS.txt'


from results import *
from PathLength import *

print 'reading data file...'
execfile(filename)# 'data' variable is read


#data = data[0:2]
print 'Calculating'
avgPathLength = sw_result(data,pathLength_digraph)
print 'done'


##def avgPl(all_pairs):
##    sum=0
##    count =0
##    for start,val_dic in all_pairs.iteritems():
##        for end,value in val_dic.iteritems():
##            if(not value==0):
##                sum +=value
##                count+=1
##    return sum/(1.0*count)
        


f = open('sws_pl.txt','w')
f.write('#n\tk\t\p\tPathLength\n')
for n,kp in sorted(avgPathLength.iteritems()):
    for k,p_pl in sorted(kp.iteritems()):
        for p,pl in sorted(p_pl.iteritems()):
            f.write('%s\t%s\t%s\t%0.2f\n'%(n,k,p,pl) )
        f.write('\n')
f.close()

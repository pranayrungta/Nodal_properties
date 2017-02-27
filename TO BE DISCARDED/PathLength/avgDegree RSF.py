from sample import *

filename = 'DSF.txt'

execfile(filename)# 'data' variable is read

#-------to print avg degree-----------
##result = rsf_result(data,avgDegree)
##print "n\tk\tavgDegree"
##for n,kv in sorted( result.iteritems() ):
##    for k,v in sorted( kv.iteritems() ):
##        print n,"\t",k,"\t",v
##    print 
#------------------------------------



import networkx as nx
for args,connections in data:
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    print args,nx.average_shortest_path_length(G)

##graph_pos = nx.spring_layout(G)
##import matplotlib.pyplot as plt
##nx.draw_networkx_edges(G, graph_pos)
##nx.draw_networkx_nodes(G, graph_pos,
##                       nodelist=range(len(connections)),
##                       node_color='b',
##                       node_size=500,
##                       alpha=0.8)
##nx.draw_networkx_labels(G,graph_pos,font_size=16)
##plt.show()






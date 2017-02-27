from sample import *

filename = './../../data_python/DSF.txt'
execfile(filename)# 'data' variable is read

import networkx as nx
for args,connections in data:
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    print args,nx.average_shortest_path_length(G)

filename = 'data/RSF_k=2_ic=100.txt'
outfilename = 'data/clc_RSF_k=2_ic=100.txt'

data = eval( open(filename,'r').read() )

import networkx as nx
def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G


for i,(args,links) in enumerate(data):
    print args
    graph = netx_graph(links)
    btc = nx.closeness_centrality(graph)
    data[i].append(btc)

f = open(outfilename,'w')
f.write('# list of [args,nbrs,btc] \n')
f.write('# dictionary : args, links, btc \n')
f.write(str(data))
f.close()

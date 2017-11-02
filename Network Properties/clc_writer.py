source = './../../Network Properties/data/'
filename = 'RSF_n=200_k=1_ic=1000.txt'
outfilename = source+'clc_'+filename

data = eval( open(source+filename,'r').read() )

import networkx as nx
def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.items():
        for end in links:
            G.add_edge(start, end)
    return G


for i,(tag,links) in enumerate(data):
    print( i, tag )
    graph = netx_graph(links)
    btc = nx.closeness_centrality(graph)
    data[i].append(btc)

import pprint
with open(outfilename,'w') as f:
    f.write('# list of [ tag, nbrs, clc ] \n')
    pp = pprint.PrettyPrinter(indent=4,width=150,stream=f)
    pp.pprint(data)

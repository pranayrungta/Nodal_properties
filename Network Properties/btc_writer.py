source = './../../Network Properties/data/'
filename = 'Star_n=100.txt'
outfilename = source+'btc_'+filename

data = eval( open(source+filename,'r').read() )

import networkx as nx
def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G


for i,(tag,links) in enumerate(data):
    print i,tag
    graph = netx_graph(links)
    btc = nx.betweenness_centrality(graph)
    data[i].append(btc)

import pprint
with open(outfilename,'w') as f:
    f.write('# list of [ tag, nbrs, btc ] \n')
    pp = pprint.PrettyPrinter(indent=4,stream=f)
    pp.pprint(data)

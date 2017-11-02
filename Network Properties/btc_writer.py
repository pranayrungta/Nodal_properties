source = './../../Network Properties/data/'
filename = 'RSF_n=50_k=1_ic=100.txt'
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
    print i+1,tag
    graph = netx_graph(links)
    btc = nx.betweenness_centrality(graph)
    data[i].append(btc)

import pprint
with open(outfilename,'w') as f:
    f.write('# list of [ tag, nbrs, btc ] \n')
    pp = pprint.PrettyPrinter(indent=4,width=150,stream=f)
    pp.pprint(data)

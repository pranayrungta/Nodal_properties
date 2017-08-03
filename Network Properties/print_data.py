filename = 'data/RSF_k=1_ic=100.txt'
data = eval( open(filename,'r').read() )
nbrs = data[0][1]
node_size = 100

import networkx as nx
def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G

import matplotlib.pyplot as plt

g = netx_graph(nbrs)
degree = g.degree()
clc = nx.closeness_centrality(g)
btc = nx.betweenness_centrality(g)

with open('btc_clc_deg.txt','w') as f:
    h = ['n','k','c','b',]
    f.write( '\t'.join([h[0],h[1],h[2],h[3]]) + '\n')
    for i in sorted(nbrs):
        f.write('%s\t%s\t%0.5f\t%0.5f\n'%(i,degree[i],clc[i],btc[i]))
##
###pos = nx.circular_layout(g)
###pos = nx.random_layout(g)
###pos = nx.shell_layout(g)
##pos = nx.spring_layout(g)
###pos = nx.spectral_layout(g)
###pos = nx.fruchterman_reingold_layout(g)
##cm = 'jet'
##def plot_arg(xValues):
##    return { 'cmap' : plt.get_cmap(cm),
##             'alpha': 0.9,
##             'node_list' : xValues.keys(),
##             'node_color' : xValues.values(),
##             'node_size' : 100,
##             'pos' : pos,
##            }
##def draw_colorbar(xValues):
##    vmax = max( xValues.values() )
##    vmin = min( xValues.values() )
##    sm = plt.cm.ScalarMappable(cmap=plt.get_cmap(cm),
##                norm=plt.Normalize(vmin=vmin, vmax=vmax))
##    sm._A = []
##    plt.colorbar(sm, shrink = 0.7)
##
##plt.clf()
##nx.draw(g,**plot_arg(clc))
##draw_colorbar(clc)
###plt.show()
##plt.savefig('clc.png')
##
##plt.clf()
##nx.draw(g,**plot_arg(degree))
##draw_colorbar(degree)
##plt.savefig('degree.png')
##
##plt.clf()
##nx.draw(g,**plot_arg(btc))
##draw_colorbar(btc)
##plt.savefig('btc.png')
##
##
##nodes = {}
##for i in range(100):
##	nodes[i]=i
##plt.clf()
##nx.draw(g,**plot_arg(nodes))
##draw_colorbar(nodes)
##plt.savefig('nodes.png')

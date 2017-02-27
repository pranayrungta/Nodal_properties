filename = 'RSF.txt'

execfile(filename)# 'data' variable is read

import networkx as nx
def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G

def data_point_to_str(nbr,btc):
    x = [nbr for (i,nbr) in sorted(links.iteritems())]
    btc = [[bt,nb] for (nb,bt) in sorted(btc.iteritems())]
    data_point = 'data_point(%s,%s)'%(str(x),str(btc))
    data_point = data_point.replace('[','{')
    data_point = data_point.replace(']','}')
    return data_point


head = '''
vector<data_point> data;
void fill_data()
{
data.reserve(%s);

'''%len(data)
f = open('data.cpp','w')
f.write(head)
for args,links in data:
    print args
    graph = netx_graph(links)
    btc = nx.betweenness_centrality(graph)
    f.write('data.push_back(%s);\n'%data_point_to_str(links,btc))
f.write('};')
f.close()

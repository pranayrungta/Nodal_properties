import networkx as nx

def netx_graph(connections):
    G=nx.Graph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G

def netx_digraph(connections):
    G=nx.DiGraph()
    for start,links in connections.iteritems():
        for end in links:
            G.add_edge(start, end)
    return G


def pathLength(connections):
    G = netx_graph(connections)
    return nx.average_shortest_path_length(G)

def pathLength_digraph(connections):
    G = netx_digraph(connections)
    return nx.average_shortest_path_length(G)


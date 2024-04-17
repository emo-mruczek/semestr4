import networkx as nx
from pyvis.network import Network 
from random import randint
import numpy as np

m = 1500

edges = [(1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 10), (10, 1), (11, 12), (12, 13), (13, 14), (14, 15), (15, 16), (16, 17), (17, 11), (18, 19), (19, 20), (20, 18), (1, 11), (3, 12), (4, 13), (5, 14), (7, 15), (9, 17), (13, 19), (15, 20), (16, 18)]
nodes = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

# wygenerowana funkcja przy uzyciu generate_N
N = [[5, 9, 6, 3, 8, 7, 1, 1, 5, 3, 7, 2, 9, 8, 2, 2, 2, 3, 7, 1], [2, 9, 5, 4, 7, 8, 6, 1, 2, 8, 5, 6, 2, 9, 8, 8, 5, 5, 7, 8], [5, 9, 1, 7, 3, 6, 8, 8, 1, 4, 4, 10, 5, 5, 5, 1, 5, 6, 7, 2], [6, 2, 1, 7, 5, 2, 3, 4, 10, 1, 2, 7, 2, 5, 9, 5, 6, 8, 10, 1], [6, 1, 9, 8, 7, 8, 5, 3, 1, 4, 8, 4, 9, 8, 1, 4, 1, 2, 6, 3], [3, 10, 7, 1, 5, 4, 5, 1, 3, 2, 10, 6, 6, 7, 5, 5, 10, 7, 8, 3], [10, 4, 7, 2, 1, 8, 5, 4, 9, 6, 4, 1, 4, 5, 9, 9, 3, 9, 7, 2], [1, 1, 9, 1, 9, 6, 8, 4, 10, 10, 3, 4, 5, 9, 9, 7, 2, 3, 1, 10], [8, 7, 6, 4, 8, 5, 2, 5, 2, 10, 2, 1, 8, 7, 9, 3, 4, 1, 5, 5], [1, 7, 1, 9, 5, 7, 7, 7, 7, 4, 7, 6, 5, 10, 8, 9, 8, 8, 1, 3], [8, 5, 3, 5, 9, 10, 4, 6, 1, 8, 4, 7, 6, 9, 3, 5, 2, 7, 4, 2], [9, 1, 2, 7, 4, 5, 8, 3, 5, 5, 3, 4, 9, 4, 6, 8, 2, 4, 10, 10], [4, 1, 1, 3, 2, 8, 8, 10, 4, 10, 5, 1, 10, 4, 3, 2, 6, 8, 2, 4], [8, 10, 7, 4, 7, 10, 1, 2, 8, 3, 6, 5, 6, 7, 8, 9, 8, 10, 10, 6], [5, 6, 1, 6, 7, 3, 9, 9, 3, 3, 5, 10, 8, 6, 1, 8, 7, 4, 9, 8], [9, 9, 1, 6, 6, 1, 3, 1, 3, 1, 10, 4, 8, 7, 3, 3, 1, 10, 4, 7], [8, 3, 9, 8, 5, 6, 8, 4, 1, 9, 6, 5, 7, 1, 10, 7, 7, 4, 2, 6], [5, 4, 5, 3, 6, 5, 9, 8, 6, 6, 3, 4, 3, 6, 5, 4, 4, 1, 1, 7], [10, 6, 9, 5, 7, 3, 8, 4, 4, 6, 5, 7, 1, 4, 10, 2, 7, 4, 1, 9], [9, 6, 10, 5, 1, 6, 9, 2, 5, 10, 2, 10, 7, 6, 3, 1, 2, 8, 2, 1]]    

#generuje moj graf
def generate_graph():
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)
    return G

# do narysowania powyzszego grafu
def draw(G):
    net = Network()
    net.add_nodes(nodes)
    net.add_edges(edges)
    net.show('graph.html', notebook=False)

def generate_N(nodes, max):
    arr = [[0]*nodes]*nodes
#    for i in range (nodes):
#        for j in range (nodes):
#            arr[i][j] = randint(1, max)  #co? 

    return [[randint(1, max) for j in range(nodes)] for i in range(nodes)]

def flow(G):
    nx.set_edge_attributes(G, 0, 'a')
    for i in range(len(nodes)):
        for j in range(len(nodes)):
            path = nx.shortest_path(G, nodes[i], nodes[j])
            for p in range(len(path) - 1):
                G[path[p]][path[p+1]]['a'] += N[i][j]

def capacity(G):
    nx.set_edge_attributes(G, 0, 'c')
    for i, j in G.edges:
        G[i][j]['c'] = 50 * (G[i][j]['a'] // 10) * m


def main():
    G = generate_graph()
    #draw(G)
    #arr = generate_N(20, 10)
    # print(np.matrix(N))
    #print(G)

    flow(G)
    for edge in G.edges(data=True):
       print(f"Edge {edge[0]} -> {edge[1]}: Flow = {edge[2]['a']}")
    capacity(G)
    for edge in G.edges(data=True):
       print(f"Edge {edge[0]} -> {edge[1]}: Cap = {edge[2]['c']}")
    

if __name__ == "__main__":
    main()

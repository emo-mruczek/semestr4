import networkx as nx
from pyvis.network import Network 
import random
import numpy as np
from copy import deepcopy
from random import randint

m = 128

edges = [(1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 10), (10, 1), (11, 12), (12, 13), (13, 14), (14, 15), (15, 16), (16, 17), (17, 11), (18, 19), (19, 20), (20, 18), (1, 11), (3, 12), (4, 13), (5, 14), (7, 15), (9, 17), (13, 19), (15, 20), (16, 18)]
nodes = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

# wygenerowana funkcją macież natężeń
N = [[0, 9, 6, 10, 5, 4, 5, 6, 4, 2, 4, 1, 8, 2, 8, 5, 8, 2, 4, 6], [6, 0, 10, 3, 4, 4, 7, 10, 7, 2, 7, 6, 2, 3, 4, 8, 2, 5, 2, 10], [1, 1, 0, 4, 8, 4, 6, 1, 7, 10, 5, 2, 7, 2, 5, 8, 9, 7, 9, 9], [1, 4, 1, 0, 10, 6, 3, 10, 2, 10, 3, 1, 3, 10, 1, 3, 2, 1, 6, 3], [2, 6, 8, 3, 0, 2, 5, 5, 3, 1, 7, 4, 4, 2, 4, 1, 8, 5, 5, 10], [3, 2, 1, 7, 10, 0, 1, 3, 6, 3, 6, 3, 4, 8, 1, 4, 8, 4, 4, 4], [10, 1, 2, 9, 3, 6, 0, 10, 2, 1, 10, 4, 9, 2, 6, 5, 3, 9, 7, 5], [6, 7, 7, 7, 9, 5, 4, 0, 6, 4, 10, 1, 7, 1, 3, 7, 4, 3, 6, 9], [9, 9, 1, 9, 4, 6, 9, 2, 0, 2, 10, 9, 1, 7, 2, 6, 1, 3, 4, 6], [3, 5, 5, 7, 10, 3, 9, 6, 10, 0, 7, 10, 10, 1, 8, 10, 3, 1, 2, 2], [4, 7, 8, 2, 10, 7, 1, 2, 7, 7, 0, 6, 6, 3, 8, 5, 5, 3, 5, 6], [1, 7, 6, 3, 6, 1, 2, 2, 6, 2, 4, 0, 1, 6, 5, 4, 8, 10, 10, 10], [4, 2, 2, 1, 4, 4, 7, 1, 10, 8, 10, 9, 0, 3, 3, 8, 4, 8, 3, 8], [8, 2, 6, 1, 4, 9, 3, 4, 7, 10, 1, 6, 1, 0, 10, 10, 9, 2, 3, 8], [1, 8, 9, 6, 7, 6, 8, 4, 6, 2, 5, 3, 4, 5, 0, 6, 4, 3, 5, 4], [1, 5, 10, 4, 3, 3, 2, 5, 2, 2, 7, 3, 8, 3, 8, 0, 5, 7, 10, 2], [4, 9, 6, 6, 1, 6, 4, 6, 6, 8, 5, 5, 5, 3, 7, 5, 0, 2, 9, 1], [3, 7, 6, 3, 5, 5, 5, 8, 6, 9, 8, 9, 4, 10, 2, 8, 1, 0, 6, 5], [4, 6, 3, 6, 3, 9, 1, 6, 5, 7, 7, 5, 4, 10, 6, 9, 6, 8, 0, 4], [10, 2, 1, 1, 6, 4, 7, 2, 4, 5, 1, 7, 9, 8, 7, 9, 10, 10, 9, 0]]
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

    return [[randint(1, max) if i != j else 0 for j in range(nodes)] for i in range(nodes)]

def flow(G, M = N):
    nx.set_edge_attributes(G, 0, 'a')
    for i in range(len(nodes)):
        for j in range(len(nodes)):
            path = nx.shortest_path(G, nodes[i], nodes[j])
            for p in range(len(path) - 1):
                G[path[p]][path[p+1]]['a'] += M[i][j]

def capacity(G, M = m):
    nx.set_edge_attributes(G, 0, 'c')
    for i, j in G.edges:
        G[i][j]['c'] = 50 * (G[i][j]['a'] // 10 + 10) * M

def reliability(G, T_max, p, M = m, matrix = N):
    successes = 0
   # G_sum = sum(sum(row) for row in N) # będziemy dzielic przez sumę wszystkich elementow macierzy natęzen 
    for _ in range(1000):
        tester = deepcopy(G)
        for edge in G.edges:
            ran = random.random() # wygeneruje floata od 0.0 do 1.0
            if ran > p:
                tester.remove_edge(*edge)
        if not nx.is_connected(tester):
               # print("broken")
                continue
        else:
                flow(tester)
                res = T(tester, matrix)
                #print(res)
                if res and res < T_max:
                    successes += 1
                    #print(successes)
                #else:
                    #print("failed")
    return successes/1000
                    

def T(G, matrix = N):
    ret = 0 
    sum_edg = 0 
    for edg in matrix:
        for val in edg:
            sum_edg += val
    for i, j in G.edges: # sumujemy po krawedziach
        if (G[i][j]['a'] < G[i][j]['c'] / m):
            ret += G[i][j]['a'] / (G[i][j]['c'] / m - G[i][j]['a'])
        else:
            return None # nie mozna dzielic przez 0, co nie?
    return 1 / sum_edg * ret

def test_N(G, T_max, p, M = m):
    print("Testing: increasing N")
    
   # tester_N = deepcopy(N)
   # res = [reliability(G, T_max, p, m, tester_N)]
    #for _ in range(10):
   #         i, j = random.randint(0, 19), random.randint(0, 19)
       #     if i == j:
      #          break
     #       tester_N[i][j] += 10 
    #        flow(G, tester_N)
   #         result = reliability(G, T_max, p, m, tester_N)
    #        print(result)
   ##         res.append
    #print(res)
    


    tester_N = generate_N(20, 50)
    init = reliability(G, T_max, p, m, tester_N)
    print(f"Init reliability: {init} ")
    for i in range(0, 50, 5):
        # zwiekszam natężenie
        for j in range(len(tester_N)):
            for k in range(len(tester_N)):
                if j == k:
                    continue
                else:
                    tester_N[j][k] += i
        flow(G, tester_N)
        capacity(G)
        res = reliability(G, T_max, p)
        print(f"Increased for {i}: current reliability: {res}")


def test_flow(G, T_max, p, M=m):
    print("Testing: increasing flow")
    test_matrix = generate_N(20, 50)
    print(np.matrix(test_matrix))
    flow(G, test_matrix)
    capacity(G)
    for k in range(10):
        for i, j in G.edges:
            G[i][j]['c'] += 50
        res = reliability(G, T_max, p)
        print(f"Increased for {k*50}: current reliability: {res}")

def test_edges(G, T_max, p, M=m):
    print("Testing: increasing number of edges")
    


def main():
    G = generate_graph()
    ##draw(G)
    #arr = generate_N(20, 10)
    #print(arr)
   # print(np.matrix(N))
   # print(G)

    flow(G)
   # for edge in G.edges(data=True):
   #    print(f"Edge {edge[0]} -> {edge[1]}: Flow = {edge[2]['a']}")
    capacity(G)
   # for edge in G.edges(data=True):
   #    print(f"Edge {edge[0]} -> {edge[1]}: Cap = {edge[2]['c']}")
    #ret = reliability(G, 0.1, 0.8)
    #print("ret:")
   #print(ret)
   # test_flow(G, 0.25, 0.75)


if __name__ == "__main__":
    main()

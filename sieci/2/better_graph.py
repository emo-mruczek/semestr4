import networkx as nx
from pyvis.network import Network 
import random
import numpy as np
from copy import deepcopy
from random import randint

SIZE = 256

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


def flow(graph, matrix):
    """Generates flow and assigns it to a Graph from given intensity matrix

    Args:
        graph (networkx Graph): Graph to assign flow to
        matrix (2D Integer List): intensity matrix of Bits per sec for a route for node i to j
    """
    nx.set_edge_attributes(graph, 0, "flow")
    node_count = nx.number_of_nodes(graph)
    for i in range(node_count):
        for j in range(node_count):
            path = nx.shortest_path(graph, i, j)
            for n in range(len(path) - 1):
                graph[path[n]][path[n + 1]]["a"] += matrix[i][j]



def capacity(G):
    nx.set_edge_attributes(G, 0, "c")
    for i, j in G.edges:
        G[i][j]['c'] = (G[i][j]['a'] * 10) + SIZE

def experiment1(graph, matrix, T_max, p, m, iterations=10, step=10):
    test_graph = deepcopy(graph)
    test_matrix = deepcopy(matrix)
    results = [reliability(test_graph, test_matrix, T_max, p, m)]
    for _ in range(iterations):
        while True:
            i, j = random.randint(0, 19), random.randint(0, 19)
            if i != j:
                break
        test_matrix[i][j] += step
        append_flow(test_graph, i, j, step)
        results.append(reliability(test_graph, test_matrix, T_max, p, m))
    return results

def T(graph, matrix_sum, m):
    T = 0
    #print(matrix_sum)
    for i, j in graph.edges:
        a = graph[i][j]["a"]
        c = graph[i][j]["c"]
        if a >= c / m:
            #print("None")
            return None
        else:
            T += a / (c / m - a)
    #print(T / matrix_sum)
    return T / matrix_sum


def reliability(graph, matrix, T_max, p, m, iterations=100, intervals=10):
    successful_trials = 0
    matrix_sum = sum(sum(row) for row in matrix)
    base_t = T(graph, matrix_sum, m)
    for _ in range(iterations):
        trial_graph = deepcopy(graph)
        for _ in range(intervals):
            broken = [e for e in nx.edges(trial_graph) if random.random() > p]
            if broken:
                trial_graph.remove_edges_from(broken)
                if not nx.is_connected(trial_graph):
                    break
                flow(trial_graph, matrix)
                t = T(trial_graph, matrix_sum, m)
                #print(t)
            else:
                t = base_t
                #print(t)
            if not t or t >= T_max:
                #print("wrong")
                break
            successful_trials += 1
    return successful_trials / (iterations * intervals)


def append_flow(graph, i, j, change):
    path = nx.shortest_path(graph, i, j)
    for n in range(len(path) - 1):
        graph[path[n]][path[n + 1]]["a"] += change

def t1(G, N):
    suma = sum(sum(r) for r in N)
    M = [2]
    P = [0.95]
    TMAX = [T(G, suma, 4)]
    for p in P:
        for m in M:
            res = []
            for Tmax in TMAX:
                for i in list(enumerate(experiment1(G, N, Tmax, p, m, step=(SIZE*25), iterations=100))):
                    res.append([Tmax, i[0], i[1]])

def main():
    G = generate_graph()
    #draw(G)
    flow(G, N)
    capacity(G)
    print(G)
    t1(G, N)





if __name__ == "__main__":
    main()

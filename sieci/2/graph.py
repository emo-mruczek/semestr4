#TODO: moje spodoby zrobienia rzeczy
#TODO: wykresy
#TODO: sprawko

import networkx as nx
from pyvis.network import Network
import random
from copy import deepcopy
from random import randint

SIZE = 256

my_N = [[0, 9, 6, 10, 5, 4, 5, 6, 4, 2, 4, 1, 8, 2, 8, 5, 8, 2, 4, 6],
        [6, 0, 10, 3, 4, 4, 7, 10, 7, 2, 7, 6, 2, 3, 4, 8, 2, 5, 2, 10],
        [1, 1, 0, 4, 8, 4, 6, 1, 7, 10, 5, 2, 7, 2, 5, 8, 9, 7, 9, 9],
        [1, 4, 1, 0, 10, 6, 3, 10, 2, 10, 3, 1, 3, 10, 1, 3, 2, 1, 6, 3],
        [2, 6, 8, 3, 0, 2, 5, 5, 3, 1, 7, 4, 4, 2, 4, 1, 8, 5, 5, 10],
        [3, 2, 1, 7, 10, 0, 1, 3, 6, 3, 6, 3, 4, 8, 1, 4, 8, 4, 4, 4],
        [10, 1, 2, 9, 3, 6, 0, 10, 2, 1, 10, 4, 9, 2, 6, 5, 3, 9, 7, 5],
        [6, 7, 7, 7, 9, 5, 4, 0, 6, 4, 10, 1, 7, 1, 3, 7, 4, 3, 6, 9],
        [9, 9, 1, 9, 4, 6, 9, 2, 0, 2, 10, 9, 1, 7, 2, 6, 1, 3, 4, 6],
        [3, 5, 5, 7, 10, 3, 9, 6, 10, 0, 7, 10, 10, 1, 8, 10, 3, 1, 2, 2],
        [4, 7, 8, 2, 10, 7, 1, 2, 7, 7, 0, 6, 6, 3, 8, 5, 5, 3, 5, 6],
        [1, 7, 6, 3, 6, 1, 2, 2, 6, 2, 4, 0, 1, 6, 5, 4, 8, 10, 10, 10],
        [4, 2, 2, 1, 4, 4, 7, 1, 10, 8, 10, 9, 0, 3, 3, 8, 4, 8, 3, 8],
        [8, 2, 6, 1, 4, 9, 3, 4, 7, 10, 1, 6, 1, 0, 10, 10, 9, 2, 3, 8],
        [1, 8, 9, 6, 7, 6, 8, 4, 6, 2, 5, 3, 4, 5, 0, 6, 4, 3, 5, 4],
        [1, 5, 10, 4, 3, 3, 2, 5, 2, 2, 7, 3, 8, 3, 8, 0, 5, 7, 10, 2],
        [4, 9, 6, 6, 1, 6, 4, 6, 6, 8, 5, 5, 5, 3, 7, 5, 0, 2, 9, 1],
        [3, 7, 6, 3, 5, 5, 5, 8, 6, 9, 8, 9, 4, 10, 2, 8, 1, 0, 6, 5],
        [4, 6, 3, 6, 3, 9, 1, 6, 5, 7, 7, 5, 4, 10, 6, 9, 6, 8, 0, 4],
        [10, 2, 1, 1, 6, 4, 7, 2, 4, 5, 1, 7, 9, 8, 7, 9, 10, 10, 9, 0]]

my_edges = [(0, 1), (2, 3), (1, 4), (3, 4), (4, 5), (5, 6), (5, 7), (7, 8), (5, 8), (5, 12), (5, 9), (9, 10), (9, 11), (11,14), (14, 13), (9,16), (16, 15), (16,19), (16,18), (18,17)]

def generate_graph():
    G = nx.Graph()
    G.add_edges_from(my_edges)
    N = [[j * SIZE for j in i] for i in my_N]
    flow(G, N)
    capacity(G)
    return G


def draw(G):
    net = Network()
    #net.add_nodes(nodes)
    #net.add_edges(edges)
    net.show('graph.html', notebook=False)

def generate_N(nodes, max):
    arr = [[0]*nodes]*nodes
#    for i in range (nodes):
#        for j in range (nodes):
#            arr[i][j] = randint(1, max)  #co?

    return [[randint(1, max) if i != j else 0 for j in range(nodes)] for i in range(nodes)]

def flow(G, matrix):
    nx.set_edge_attributes(G, 0, 'a')
    count = nx.number_of_nodes(G)
    for i in range(count):
        for j in range(count):
            path = nx.shortest_path(G, i, j)
            for n in range(len(path) - 1):
                G[path[n]][path[n + 1]]['a'] += matrix[i][j]
def capacity(G):
    nx.set_edge_attributes(G, 0, 'c')
    for i, j in G.edges:
        G[i][j]['c'] = ((G[i][j]['a'] * 10) + SIZE)

def T(G, curr_sum, m):
    curr = 0
    for i, j in G.edges:
        if G[i][j]['a'] >= G[i][j]['c'] / m:
            #print("a za duze!)
            return None
        else:
            curr +=G[i][j]['a'] / (G[i][j]['c'] / m - G[i][j]['a'])
    ret = curr / curr_sum
    return ret

def is_broken(G, p):
    edges = []
    for edge in nx.edges(G):
        if random.random() > p:
                edges.append(edge)
    return edges
def reliability(G, matrix, Tmax, p, m, iterations=100, intervals=10):
    successes = 0
    curr_sum = sum(sum(row) for row in matrix)
    base = T(G, curr_sum, m)
    for _ in range(iterations):
        tester = deepcopy(G)
        for _ in range(intervals):
            #broken = [e for e in nx.edges(tester) if random.random() > p]
            broken = is_broken(tester, p)
            if broken:
                tester.remove_edges_from(broken)
                if not nx.is_connected(tester):
                    break
                flow(tester, matrix)
                t = T(tester, curr_sum, m)
                # print(t)
            else:
                t = base
                # print(t)
            if not t or t >= Tmax:
                # print("wrong")
                break
            successes += 1
    ret = successes / (iterations * intervals)
    return ret

def test_N(G, matrix):
    print("Zwiększanie macierzy N, wartości niezawodności:")

    curr_sum = sum(sum(r) for r in matrix)
    m = 2
    p = 0.95
    Tmax = T(G, curr_sum, 4)
    step = (SIZE * 25)
    tester = deepcopy(matrix)
    for k in range(100):
        while True:
            i, j = random.randint(0, 19), random.randint(0, 19)
            if i != j:
                break
        tester[i][j] += step
        path = nx.shortest_path(G, i, j)
        for n in range(len(path) - 1):
            G[path[n]][path[n + 1]]['a'] += step
        current_reliability = reliability(G, tester, Tmax, p, m)
        print(f"krok: {step*k}, niezawodność: {current_reliability}")

def test_cap(G, matrix):

    curr_sum = sum(sum(r) for r in matrix)
    m = 2
    p = 0.95
    Tmax = T(G, curr_sum, 4)

    for k in range(1):
        for i, j in G.edges:
            G[i][j]['c'] += SIZE
        current_reliability = reliability(G, matrix, Tmax, p, m)
        print(f"krok: {SIZE * k}, niezawodność: {current_reliability}")

def test_edges(G, matrix):
    curr_sum = sum(sum(r) for r in matrix)
    m = 2
    p = 0.95
    Tmax = T(G, curr_sum, 4)

    all_caps = nx.get_edge_attributes(G, 'c').values()
    caps_sum = sum(all_caps)
    caps_len = len(all_caps)
    caps_new = caps_sum / caps_len
    without_edge = list(nx.non_edges(G))
    for k in range(1):
        i, j = random.sample(without_edge, 1)[0]
        without_edge.remove((i, j))
        G.add_edge(i, j)
        G[i][j]['c'] = caps_new
        flow(G, matrix)
        current_reliability = reliability(G, matrix, Tmax, p, m)
        print(f"krok: {k}, niezawodność: {current_reliability}")

def main():
    G = generate_graph()
    #test_N(G, N)
    #test_cap(G, N)
    #test_edges(G, N)

if __name__ == "__main__":
    main()

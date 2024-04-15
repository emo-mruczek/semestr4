import networkx as nx
from pyvis.network import Network 


edges = [(1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 10), (10, 1), (11, 12), (12, 13), (13, 14), (14, 15), (15, 16), (16, 17), (17, 11), (18, 19), (19, 20), (20, 18), (1, 11), (3, 12), (4, 13), (5, 14), (7, 15), (9, 17), (13, 19), (15, 20), (16, 18)]
nodes = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]


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
    net.show("graph.html")

    


def main():
    G = generate_graph()
    draw(G)


if __name__ == "__main__":
    main()

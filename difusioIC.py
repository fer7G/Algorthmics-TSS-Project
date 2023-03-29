import warnings
warnings.filterwarnings("ignore")

import random
import networkx as nx
import matplotlib.pyplot as plt

# Struct for undirected graph
class Graph:
    def __init__(self, n):
        self.numNodes = n
        self.adjList = [[] for i in range(n)]
        
    def addEdge(self, u, v):
        self.adjList[u].append(v)
        self.adjList[v].append(u)

# Simulate IC diffusion process
def simulateIC(G, p, S, nx_G, pos, node_colors):
    # Set of influenced nodes
    influenced = [False] * G.numNodes
    # Set of active nodes (per iteration)
    active = []
    
    # Number of steps
    t = 0

    # Order of nodes as stored in the graph, lo necesitamos
    node_order = list(nx_G.nodes())

    # Activate initial set of nodes
    for vertex in S:
        influenced[vertex] = True
        active.append(vertex)

    # Correct "order" for node color list, if we don't do this the nodes are painted wrong
    i = 0
    for node in node_order:
        node_colors[i] = 'r' if influenced[node] else 'grey'
        i += 1

    # Paint the graph for the first time
    nx.draw_networkx_nodes(nx_G, pos, nodelist=node_order, node_color=node_colors, cmap=plt.cm.Reds)
    plt.draw()
    plt.pause(1)

    # Continue until no more active nodes
    while active:
        t += 1
        numCurrentActive = len(active)
        # Process all active nodes in the current layer
        for i in range(numCurrentActive):
            v = active.pop(0)
            # Check neighbours of v
            for neighbour in G.adjList[v]:
                # If neighbor is not already active, try to activate it
                if not influenced[neighbour]:
                    r = random.random() # random number between 0 and 1
                    if r < p:
                        influenced[neighbour] = True
                        active.append(neighbour)

        # Checking again if we need to color new nodes
        # Correct "order" for node color list, if we don't do this the nodes are painted wrong
        i = 0
        for node in node_order:
            node_colors[i] = 'r' if influenced[node] else 'grey'
            i += 1

        nx.draw_networkx_nodes(nx_G, pos, nodelist=node_order, node_color=node_colors, cmap=plt.cm.Reds)
        plt.draw()
        plt.pause(1)

    count = 0
    for node in influenced:
        if node:
            count += 1
    return count, t, influenced

def readInput():
    n, m = map(int, input("Enter number of nodes and number of edges: ").split())
    G = Graph(n)
    print(f"Enter {m} edges:")
    for i in range(m):
        u, v = map(int, input().split())
        G.addEdge(u, v)
    p = float(input("Enter probability for IC model: "))
    s = int(input("Enter number of nodes in the initial seed: "))
    print(f"Enter {s} nodes for the initial seed:")
    S = list(map(int, input().split()))
    return G, p, S

if __name__ == "__main__":
    G, p, S = readInput()

    # Convert adjacency list to list of edges
    edge_list = []
    for u in range(G.numNodes):
        for v in G.adjList[u]:
            if (u, v) not in edge_list and (v, u) not in edge_list:
                edge_list.append((u, v))

    # Create NetworkX graph from the edge list
    nx_G = nx.Graph()
    nx_G.add_edges_from(edge_list)

    # Draw the graph
    pos = nx.spring_layout(nx_G)

    node_colors = ['grey' for _ in range(nx_G.number_of_nodes())]
    nx.draw(nx_G, pos, with_labels=True)

    # Run simulation and update the node colors
    C, t, influenced = simulateIC(G, p, S, nx_G, pos, node_colors)

    print("Size of C:", C)
    print("Value of t:", t)

    # Show the final plot
    plt.show(block=True)

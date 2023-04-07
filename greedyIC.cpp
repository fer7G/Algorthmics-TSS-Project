#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <set>
#include <ctime>
#include <chrono>
using namespace std;
typedef pair<int, int> pii;

// Struct for undirected graph
struct Graph {
    int numNodes;
    vector<vector<int> > adjList;

    // Graph constructor:
    Graph(int n) {
        numNodes = n;
        adjList.resize(n);
    }

    Graph() {
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printEdges() {
        for (int vertex = 0; vertex < adjList.size(); ++vertex) {
            for (int neighbour : adjList[vertex]) cout << vertex << " -> " << neighbour << endl;
        }
    }
};

// Simulate IC difusion process
int difusioIC(const Graph& G, double& p, set<int>& S) {
    // Set of influenced nodes
    vector<bool> influenced(G.numNodes, false);
    // Set of active nodes (nodes able to activate other nodes per iteration)
    queue<int> active;
    
    int t = 0;

    // Activate initial set of nodes
    for (int vertex : S) {
        influenced[vertex] = true;
        active.push(vertex);
    }

    // Continue untill no more active nodes
    while (not active.empty()) {
        ++t;
        int numCurrentActive = active.size();
        // Process all active nodes in the current layer
        for (int i = 0; i < numCurrentActive; ++i) {
            int v = active.front();
            active.pop();
            // Check neighbours of v
            for (int j = 0; j < G.adjList[v].size(); ++j) {
                int neighbour = G.adjList[v][j];
                 // If neighbor is not already active, try to activate it
                if (not influenced[neighbour]) {
                    double r = (double) rand() / RAND_MAX;
                    if (r < p) {
                        influenced[neighbour] = true;
                        active.push(neighbour);
                    }
                }
            }
        }
    }

    // Count all influenced nodes by S
    int count = 0;
    for (int i = 0; i < influenced.size(); ++i) if (influenced[i]) ++count;
    return count;
}

// Comparer for the priority queue
struct Compare {
    bool operator()(const pii& a, const pii& b) {
        return a.second < b.second;
    }
};

// Greedy algorithm to select the minimum influence set
set<int> greedyMinInfluenceSet(const Graph& G, double p) {
    set<int> S;
    vector<pair<int, int> > gain;
    
    priority_queue<pii, vector<pii>, Compare> Q;

    // Calcular la ganancia marginal de todos los nodos
    for (int i = 0; i < G.numNodes; ++i) {
        set<int> single_node_set;
        single_node_set.insert(i);
        int gain_val = difusioIC(G, p, single_node_set);
        // gain.push_back(make_pair(i, gain_val));
        Q.push(make_pair(i, gain_val));
    }

    // Insertar los nodos en la cola de prioridad
    // priority_queue<pair<int, int>, vector<pair<int, int> >, decltype(&compare)> Q(compare, gain);

    // Añadir el primer nodo de la cola Q a S y quitarlo de la cola
    S.insert(Q.top().first);
    Q.pop();

    // Calcular la difusión de S
    int diffusion = difusioIC(G, p, S);

    // Mientras la cola Q no esté vacía y difusio(G, p, S) != |V|
    while (!Q.empty() && diffusion != G.numNodes) {
        int current_node = Q.top().first;

        // Añadir el primer nodo de la cola Q a S y quitarlo de la cola, si el nodo no está en S
        if (S.find(current_node) == S.end()) {
            S.insert(current_node);
            diffusion = difusioIC(G, p, S);
        }
        Q.pop();
    }

    return S;
}

// Read a Graph (adapted for dimacs files)
Graph readGraph() {
    char p;
    string edge;
    cin >> p >> edge;
    int n, m;
    cin >> n >> m;

    Graph G(n);

    char e;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> e >> u >> v;
        G.addEdge(u-1, v-1);
    }

    return G;
}

int main() {
    
    // Generate random seed for proper random values
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    // Declare and read the graph G = (V, E)
    Graph G = readGraph();

    // Set the probability for the IC model
    double p = 0.2;

    // Compute the subset with the greedy algorithm
    set<int> S = greedyMinInfluenceSet(G, p);

    cout << "Nodos semilla seleccionados:" << endl;
    for (int node : S) {
        cout << node << " ";
    }
    cout << endl;
}

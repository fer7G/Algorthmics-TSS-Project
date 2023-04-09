#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;
using Subset = vector<int>;

// Struct for undirected graph
struct Graph {
    int numNodes;
    vector<vector<int>> adjList;
    vector<bool> influenced;
    vector<int> peso;

    // Graph constructor:
    Graph(int n) : numNodes(n), adjList(n), influenced(n), peso(n) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void actualizarpesovecinos(int x) {
        for (auto neighbor : adjList[x]) ++peso[neighbor];
    }
    // Reset del grafo
    void graphreset(){
        fill(influenced.begin(), influenced.end(),false);
        fill(peso.begin(), peso.end(),0);
    }
};

int simulateLT(Graph& G, double r, Subset& S, int& t) {
    queue<int> active;
    t = -1;
    G.graphreset();
    // Activate initial set of nodes
    for (auto vertex : S) {
        G.influenced[vertex] = true;
        G.actualizarpesovecinos(vertex);
        active.push(vertex);
    }
    int n_influenced = active.size();
    queue<int> influencedAux;
    // Continue until no more active nodes
    while (!active.empty()) {
        ++t;
        int numCurrentActive = active.size();
        // Process all active nodes in the current layer
        for (int i = 0; i < numCurrentActive; ++i) {
            int v = active.front();
            active.pop();
            // Check neighbours of v
            for (auto neighbor : G.adjList[v]) {
                // If neighbor is not already active, try to activate it
                if (!G.influenced[neighbor]) {
                    double l = r * G.adjList[neighbor].size();
                    if (G.peso[neighbor] >= l) {
                        G.influenced[neighbor] = true;
                        influencedAux.push(neighbor);
                        ++n_influenced;
                    }
                }
            }
        }
        // Move influencedAux nodes to active and update their weights
        while (!influencedAux.empty()) {
            int u = influencedAux.front();
            influencedAux.pop();
            if (G.peso[u] != G.adjList[u].size()) {
                active.push(u);
                ++G.peso[u];
                for (auto neighbor : G.adjList[u]) {
                    ++G.peso[neighbor];
                }
            }
        }
    }
    return n_influenced;
}

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
        G.addEdge(u - 1, v - 1);
    }

    return G;
}

void readInputSubset(Subset& S) {
    int s;
    cout << "Enter number of nodes in the initial seed: ";
    cin >> s;
    cout << "Enter " << s << " nodes for the initial seed: ";
    for (int i = 0; i < s; ++i) {
        int u;
        cin >> u;
        S.push_back(u);
    }
}
/*
int main() {
    Graph G = readGraph();
    double r = 0.5;
    Subset S;
    readInputSubset(S);
    int t = 0;

    int C = simulateLT(G, r, S, t); // Falta hacer la funcion
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
}*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Subset = vector<int>;

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

int simulateLT(Graph& G, double& r, Subset& S, int& t) {
    // Set of influenced nodes
    vector<bool> influenced(G.numNodes, false);
    // Set of active nodes (per iteration)
    queue<int> active;
    
    t = -1;

    // Activate initial set of nodes
    for (int vertex : S) {
        influenced[vertex] = true;
        active.push(vertex);
    }

    queue<int> influencedAux;
    // Continue until no more active nodes
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
                    double l = r * G.adjList[neighbour].size(); 
                    int w = 0;
                    for(int k= 0; k< G.adjList[neighbour].size(); ++k) if(influenced[G.adjList[neighbour][k]]) ++w;
                    if (w >= l) {
                        //añadir a la cola
                        influencedAux.push(neighbour);
                    }
                }
            }
        }
        //vaciar la cola
        while(not influencedAux.empty()) {
            int u = influencedAux.front();
            influencedAux.pop();
            
            influenced[u] = true;
            active.push(u);
        }
    }
    /*for (int i = 0; i < influenced.size(); ++i){
        cout << "Nodo "<<i<<endl;
        cout << "Estado: "<<influenced[i]<<endl;
    }*/

    int count = 0;
    for (int i = 0; i < influenced.size(); ++i) if (influenced[i]) ++count; 
    return count;
}

void readInput(Graph& G, double& r, Subset& S) {
    int n, m;
    cout << "Enter number of nodes and number of edges: ";
    cin >> n >> m;
    G = Graph(n);
    cout << "Enter " << m << " edges: ";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G.addEdge(u, v);
    }
    cout << "Enter influence ratio [0, 1] for LT model: ";
    cin >> r;
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


int main () {
    Graph G;
    double r;
    Subset S;
    readInput(G, r, S);
    int t = 0;
    int C = simulateLT(G, r, S, t); // Falta hacer la funcion
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
}
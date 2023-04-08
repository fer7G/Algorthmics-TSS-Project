#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Subset = vector<int>;

// Struct for undirected graph
struct Graph {
    int numNodes;
    vector<vector<int> > adjList;
    vector<bool> influenced;

    // Graph constructor:
    Graph(int n) {
        numNodes = n;
        adjList.resize(n);
        influenced.resize(n);
    }

    Graph() {
    }
        void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }   
};

int simulateLT(Graph& G, double& r, Subset& S, int& t) {
    t = 0;

    // Activate initial set of nodes and count them
    int numSeeds = S.size();
    vector<bool> influenced(G.numNodes, false);
    for (int vertex : S) {
        influenced[vertex] = true;
    }

    // Set of active nodes (per iteration)
    queue<int> active;
    for (int vertex : S) {
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
            for (int neighbour : G.adjList[v]) {
                // If neighbor is not already active, try to activate it
                if (not influenced[neighbour]) {
                    double l = r * G.adjList[neighbour].size();
                    int numActivatedNeighbours = 0;
                    for (int neighbourOfNeighbour : G.adjList[neighbour]) {
                        if (influenced[neighbourOfNeighbour]) {
                            ++numActivatedNeighbours;
                        }
                    }
                    if (numActivatedNeighbours >= l) {
                        influencedAux.push(neighbour);
                        influenced[neighbour] = true;
                    }
                }
            }
        }
        // Transfer nodes from influencedAux to active and count them
        int numActivated = influencedAux.size();
        for (int i = 0; i < numActivated; ++i) {
            int u = influencedAux.front();
            influencedAux.pop();
            active.push(u);
        }
    }

    int count = numSeeds;
    for (bool v : influenced) {
        if (v) {
            ++count;
        }
    }
    return count;
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
        G.addEdge(u-1, v-1);
    }

    return G;
}

void readInputSubset (Subset& S) {
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

/* De momento lo dejamos asi, seguramente haya que borrar el main del greedy
int main () {
    Graph G;
    double r;
    Subset S;
    readInput(G, r);
    readInputSubset(S);
    int t = 0;
    int C = simulateLT(G, r, S, t); // Falta hacer la funcion
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
}*/
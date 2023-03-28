#include <iostream>
#include <vector>
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

// Simulate IC difusion process:
int simulateIC(Graph& G, double& p, Subset& s, int& t) {
    return 0;
}

void readInput(Graph& G, double& p, Subset& S) {
    int n, m;
    cin >> n >> m;
    G = Graph(n);
    for (int i = 0; i < m; ++i {
        int u, v;
        cin >> u >> v;
        G.addEdge(u, v);
    }
    cin >> p;
    int s;
    cin >> s;
    for (int i = 0; i < s; ++i {
        int u;
        cin >> u;
        S.push_back(u);
    }
}

int main() {
    Graph G;
    double p;
    Subset S;
    readInput(G, p, S);
    int t = 0;
    int C = simulateIC(G, p, S, t);
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
}
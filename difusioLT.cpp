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
    vector<vector<int> > adjList;
    vector<bool> influenced;
    vector<int> peso;

    // Graph constructor:
    Graph(int n) {
        numNodes = n;
        adjList.resize(n);
        influenced.resize(n);
        peso = vector<int> (n,0);
    }

    Graph() {
    }
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }   
    void actualizarpesovecinos(int x){
        for(int i= 0; i< adjList[x].size(); ++i){
            //cout << "arista de "<< x <<" :"<<adjList[x][i]<<endl;
            ++peso[adjList[x][i]];
        }
    }
    int getTotalInfluenced(){
        int retVal = 0;
        for (bool u : influenced)
            if(u)
                ++retVal;
        return retVal;
    }
};


int simulateLT(Graph& G, double& r, Subset& S, int& t) {
    queue<int> active;
    t = -1;
    // Activate initial set of nodes
    for (int i=0;  i<S.size(); i++) {
        int vertex = S[i];
        //cout<< vertex<<endl;
        G.influenced[vertex] = true;
        G.actualizarpesovecinos(vertex);
        active.push(vertex);
    }
    int n_influenced= active.size();
    queue<int> influencedAux;
    // Continue until no more active nodes
    
    while (not active.empty()) {
        ++t;
        // Process all active nodes in the current layer
        int v = active.front();
        active.pop();
        // Check neighbours of v
        for (int j = 0; j < G.adjList[v].size(); ++j) {
            int neighbour = G.adjList[v][j];
             // If neighbor is not already active, try to activate it
            if (not G.influenced[neighbour]) {
                double l = r * G.adjList[neighbour].size(); 
                if (G.peso[neighbour] >= l) {
                    influencedAux.push(neighbour);
                    ++n_influenced;
                }
            }
        } 
        //vaciar la cola
        while(not influencedAux.empty()) {
            int u = influencedAux.front();
            influencedAux.pop();
            if (not G.influenced[u] and G.peso[u] != G.adjList[u].size()){
                G.influenced[u] = true;
                active.push(u);
                G.actualizarpesovecinos(u);
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

/*/ De momento lo dejamos asi, seguramente haya que borrar el main del greedy
int main () {
    Graph G = readGraph();
    double r= 0.5;
    Subset S;
    readInputSubset(S);
    int t = 0;
    int C = simulateLT(G, r, S, t); // Falta hacer la funcion
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
}*/

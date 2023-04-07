#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;

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

    //Getters
    int getNumNodes(){
        return numNodes;
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    //Reeds
    void readEdges(int m){

        for (int i = 0; i < m; ++i) {
            int u, v;
            cout << "What's the edge " << i << " origin?" << endl;
            cin >> u;
            cout << "And, What's his destiny node?" << endl;
            cin >> v;
            addEdge(u, v);
        }

    }

    void randomInitEdges(int m){

        for (int i = 0; i < m; ++i) {
            
            int u = rand()%numNodes;
            int v = rand()%numNodes;
            
            while(u == v)
                v = rand()%numNodes;

            addEdge(u, v);
        }

    }

    void readFromFile(int m){

        char c;
        int u,v;

        for(int i = 0; i < m; ++i){
            cin >> c >> u >> v;
            addEdge(u,v);
        }

    }

    //Print
    void printEdges() {
        for (int vertex = 0; vertex < adjList.size(); ++vertex) {
            for (int neighbour : adjList[vertex]) cout << vertex << " -> " << neighbour << endl;
        }
    }
};

struct Subset{

    int numNodes;
    int seedSize;

    vector<int> S;


    //Constructors
    Subset(){
    }
    Subset(int n){
        numNodes = n;
    }

    //Getters
    int getSeedSize(){
        return seedSize;
    }

    vector<int> getVector(){
        return S;
    }

    //Reads
    void readSeed(int s){

        cout << "Enter " << s << " nodes for the initial seed: ";

        for (int i = 0; i < s; ++i) {
            int u;
            cin >> u;
            while (u < 0 and u >= numNodes) {
                cout << "That node doesn't exist! Give an index from 0 to " << numNodes - 1 << ", please." << endl;
                cin >> u;
            }
            S.push_back(u);
        }
    }

    void randomInitSeed(int s){

        for (int i = 0; i < s; ++i) {
            int u = rand()%numNodes;
            S.push_back(u);
        }

    }
};

// Simulate IC difusion process
int simulateIC(Graph& G, double& p, Subset& S, int& t) {
    // Set of influenced nodes
    vector<bool> influenced(G.numNodes, false);
    // Set of active nodes (per iteration)
    queue<int> active;
    
    t = 0;

    // Activate initial set of nodes
    for (int vertex : S.getVector()) {
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

    int count = 0;
    for (int i = 0; i < influenced.size(); ++i) if (influenced[i]) ++count; 
    return count;
}

void readInput(Graph& G, double& p, Subset& S) {

    int n, m;
    char controlChar;
    cin >> controlChar;

    if (controlChar == 'p'){

        string s;
        cin >> s;
        cin >> n >> m;

        G = Graph(n);
        G.readFromFile(m);
    } else{
    
        cout << "Enter number of nodes: ";
        cin >> n;
        cout << "Enter number of edges: ";
        cin >> m;
        G = Graph(n);

        cout << "If you prefer a Graph Random Initialitzation write R, if you wanna do it Manual write M" << endl;
        
        cin >> controlChar;

        while(controlChar != 'R' and controlChar != 'M'){
            cout << "Write and R or N, please." << endl;
            cin >> controlChar;
        }

        if(controlChar == 'M') 
            G.readEdges(m);
        
        else{
            cout << "Please, give me a Random Seed: ";
            
            int randSeed;
            cin >> randSeed;
            srand(randSeed);

            G.randomInitEdges(m);
        }
    }

    int s;

    cout << "Enter number of nodes in the initial seed: ";
    cin >> s;

    cout << "If you prefer a SeedNodes Random Initialitzation write R, if you wanna do it Manual write M" << endl;
    
    cin >> controlChar;

    while(controlChar != 'R' and controlChar != 'M'){
        cout << "Write and R or N, please." << endl;
        cin >> controlChar;
    }

    S = Subset(n);

    if (controlChar == 'M')
        S.readSeed(s);
    else
        S.randomInitSeed(s);

    cout << "Enter probability for IC model: ";
    cin >> p;

}

int main() {
    Graph G;
    double p;
    Subset S;
    readInput(G, p, S);
    cout << "NumNodes " << G.getNumNodes() << endl;
    cout << "Size of seed " << S.getSeedSize() << endl;
    
    time_t startTime = time(NULL);

    int t = 0;
    int C = simulateIC(G, p, S, t);

    time_t endTime = time(NULL);
    
    cout << "Size of C: " << C << endl;
    cout << "Value of t: " << t << endl;
    cout << "The simulation have been done in " << endTime - startTime << " seconds" << endl;

}
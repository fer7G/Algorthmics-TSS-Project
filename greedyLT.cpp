// In this greedy we will pick the vertex with the higher degree that has not been influenced
#include "difusioLT.cpp"
using namespace std;

void readDegree(const Graph& G, priority_queue<pair<int,int>>& pq) {
    for (int i = 0; i < G.numNodes; ++i) {
            pair<int,int> p;
            p.first = G.adjList[i].size();
            p.second = i;
            pq.push(p);
        }
}

void findSubset(Subset& S, priority_queue<pair<int,int>>& pq, Graph& G, double r) {
    S.push_back(pq.top().second);
    pq.pop(); 
    vector<bool> influenced(G.numNodes, false);
    int t = 0;
    while (simulateLT(G, r, S, t, influenced) != G.numNodes) {
        while (influenced[pq.top().second]) {
            pq.pop();
        }
        S.push_back(pq.top().second);
        pq.pop();
    }
}

void printSet(Subset& S) {
    cout << "Initial set: {";
    int n = S.size() - 1;
    for (int i = 0; i < n; ++i) {
        cout << S[i] << ", " ;
    }
    cout << S[n] << '}' << endl;
}

int main () {
    Graph G;
    double r;
    readInput(G, r);
    priority_queue<pair<int,int>> pq; // first = grado, second = vertice
    readDegree(G, pq);
    Subset S;
    findSubset(S, pq, G, r);
    printSet(S);
}
// In this greedy we will pick the vertex with the higher degree that has not been influenced
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <set>
#include <ctime>
#include <chrono>
#include "difusioLT.cpp"
using namespace std;
using namespace std::chrono;

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
    int t = 0;
    while (simulateLT(G, r, S, t) != G.numNodes) {
        while (G.influenced[pq.top().second]) {
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
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    Graph G= readGraph();
    double r = 0.5;
    priority_queue<pair<int,int>> pq; // first = grado, second = vertice
    readDegree(G, pq);
    Subset S;
    auto start = high_resolution_clock::now();
    findSubset(S, pq, G, r);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    printSet(S);
     cout << " en " << (double)duration.count()/1000 << " s";
}
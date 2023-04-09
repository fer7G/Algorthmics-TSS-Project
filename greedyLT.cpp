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

void printSet(Subset& S) {
    cout << "Initial set: {";
    int n = S.size() - 1;
    for (int i = 0; i < n; ++i) {
        cout << S[i] << ", " ;
    }
    cout << S[n] << '}' << endl;
}

void readDegree(Graph& G, double r, priority_queue<pair<int,int> >& pq) {
    for (int i = 0; i < G.numNodes; ++i) {
            pair<int,int> p;
            p.first = G.adjList[i].size();
            p.second = i;
            pq.push(p);
        }
}

void readGain(Graph& G, double r, priority_queue<pair<int,int> >& pq) {
    for (int i = 0; i < G.numNodes; ++i) {
            Subset s(1, i);
            int t = 0;
            pq.push(make_pair(simulateLT(G, r, s, t), i));
        }
}

void findSubset(Subset& S, priority_queue<pair<int,int> >& pq, Graph& G, double r) {
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        if(!G.influenced[node]) {
            S.push_back(node);
        }
        int t;

        //Estas 2 variables porque por algun motivo 10 != 10
        int aux1 = simulateLT(G, r, S,t);
        int aux2 = G.numNodes;

        if (aux1 == aux2) break;
    }
}

int main () {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    Graph G= readGraph();
    double r = 0.5;
    priority_queue<pair<int,int> > pq; // first = grado | millora marginal, second = vertex
    //readDegree(G, r, pq);
    readGain(G, r, pq);
    Subset S;
    auto start = high_resolution_clock::now();
    findSubset(S, pq, G, r);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    //printSet(S);
    cout << "Nodos del subset: "<< S.size()<< endl;
    cout << "en " << (double)duration.count()/1000 << " s" << endl;
}
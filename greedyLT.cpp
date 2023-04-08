#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <set>
#include <ctime>
#include <chrono>
#include <unordered_set>
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

void readDegree(const Graph& G, priority_queue<pair<int,int> >& pq) {
    for (int i = 0; i < G.numNodes; ++i) {
            pair<int,int> p;
            p.first = G.adjList[i].size();
            p.second = i;
            pq.push(p);
        }
}

void findSubset(Subset& S, priority_queue<pair<int,int> >& pq, const Graph G, double r) {
    unordered_set<int> evaluated_nodes; // conjunto de nodos ya evaluados
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        if (evaluated_nodes.count(node)) { // si el nodo ya se evaluó, saltar la evaluación
            continue;
        }
        S.push_back(node);
        evaluated_nodes.insert(node);
        int t;
        Graph Gaux = G;
        int aux1 = simulateLT(Gaux, r, S,t);
        int aux2 = G.numNodes;
        /*
        cout<<"-Nodos influenciados : "<< aux1<<endl;
        cout<<"-Numero de nodos : "<< aux2<<endl;
        cout<<"-simulateLT(Gaux, r, S,t) == G.numNodes- : "<< (simulateLT(Gaux, r, S,t) == G.numNodes)<< endl;
        cout<<"-------------------------------------"<<endl;
        */
        if (aux1 == aux2) { // evaluar el conjunto completo al final
            cout<<"hola"<<endl;
            break;
        }
    }
}



int main () {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    cout << "Hola" << endl;
    Graph G= readGraph();
    cout << "Adios" << endl;
    double r = 0.5;
    priority_queue<pair<int,int> > pq; // first = grado, second = vertice
    readDegree(G, pq);
    Subset S;
    auto start = high_resolution_clock::now();
    findSubset(S, pq, G, r);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    printSet(S);
     cout << " en " << (double)duration.count()/1000 << " s";
}
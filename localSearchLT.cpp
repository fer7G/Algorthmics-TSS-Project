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
typedef pair<int, int> pii;
using Subset = vector<int>;

// Comparer for the priority queue
struct Compare {
    bool operator()(const pii& a, const pii& b) {
        return a.second < b.second;
    }
};


// Greedy algorithm to select the minimum influence set
Subset greedyMinInfluenceSet(Graph& G, double p) {
    Subset S;
    vector<pair<int, int>> gain;
    int numNodes = G.numNodes;
    priority_queue<pii, vector<pii>, Compare> Q;

    // Calcular la ganancia marginal de todos los nodos e ir insertando en la cola de prioridad
    for (int i = 0; i < G.numNodes; ++i) {
        Subset single_node_set;
        single_node_set.push_back(i);
        int t;
        int gain_val = simulateLT(G, p, single_node_set, t);
        gain.push_back(make_pair(i, gain_val));
    }

    // Ordenar el vector de nodos por ganancia marginal
    sort(gain.begin(), gain.end(), [](auto& a, auto& b) { return a.second > b.second; });

    // Añadir el primer nodo del vector de ganancia a S
    S.push_back(gain[0].first);

    // Calcular la difusión de S
    int t;
    int diffusion = simulateLT(G, p, S, t);

    // Mientras aún haya nodos con ganancia marginal positiva y difusio(G, p, S) != |V|
    for (int i = 1; i < G.numNodes && diffusion < numNodes; ++i) {
        int current_node = gain[i].first;

        // Añadir el nodo a S si no está presente y la difusión aumenta
        Subset tempS(S);
        tempS.push_back(current_node);
        int t;
        int temp_diffusion = simulateLT(G, p, tempS, t);
        if (temp_diffusion > diffusion) {
            S = tempS;
            diffusion = temp_diffusion;
        }
    }

    return S;
}

// Local search algorithm for best improvement
void localSearch(Graph& G, double r, Subset& S) {
    bool improvement = true;
    
    while (improvement) {
        improvement = false;
        for (int node : S) {
            Subset tempS(S);
            tempS.erase(find(tempS.begin(), tempS.end(), node));
            int t0,t1;
            int currentInfluence = simulateLT(G, r, S, t0);
            int tempInfluence = simulateLT(G, r, tempS, t1);
            
            if (tempInfluence == currentInfluence && tempS.size() < S.size()) {
                improvement = true;
                S = tempS;
            }
        }
    }
}


int main() {
    
    // Generate random seed for proper random values
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    // Declare and read the graph G = (V, E)
    Graph G = readGraph();

    // Set the probability for the IC model
    double r = 0.5;

    auto start = high_resolution_clock::now();
    // Compute the subset with the greedy algorithm
    Subset S = greedyMinInfluenceSet(G, r);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Greedy solution output
    cout << "Nodos semilla seleccionados en la solución inicial:" << S.size() << " en " << (double)duration.count()/1000 << " s" << endl;

    start = high_resolution_clock::now();
    // Compute a localSearch approach from the greedy solution
    localSearch(G, r, S);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    // Local search solution output
    cout << "Nodos semilla seleccionados por la búsqueda local:" << S.size() << " en " << (double)duration.count()/1000 << " s" << endl;
}
// Local Search best improvement 
#include "difusioLT.cpp"
using namespace std;

void printNewSol (Subset& S) {
    // ESTO DEVUELVE LA MEJOR SOLUCION
    cout << "New set: { ";
    for (int i = 0; i < S.size(); ++i) {
        cout << S[i] << ' ';
    }
    cout << '}' << endl;
}

// CUENTA CUANTOS VERTICES TIENE LA NUEVA POSIBLE SOLUCION
int contNewSol (vector<bool>& v) {
    int m = v.size();
        int cont = 0;
        for (int i = 0; i < m; ++i) {
            if (v[i]) ++cont;
        }
    return cont;
}

void backtracking (vector<bool>& v, Subset& S, Graph& G, int x, int n, int& sol, double r) {
    if (x == n) {
        vector<bool> aux = v;
        int cont = contNewSol(v);
        int t = 0;

        Subset newSet(cont);
            int a = 0;
            for (int i = 0; i < n; ++i) {
                if (v[i]) {
                    newSet[a] = i;
                    ++a;
                }
            }


       
        if (cont < sol and simulateLT(G, r, newSet, t, aux) == G.numNodes) {
            sol = cont;
            S = newSet;
        }   
          
    }
    
    else {
        v[x] = true;
        backtracking(v, S, G, x+1, n, sol, r);
        v[x] = false;
        backtracking(v, S, G, x+1, n, sol, r);
    }
}



int main () {
    Graph G;
    double r;
    readInput(G, r);
    Subset S;
    readInputSubset(S);
    int n = S.size();
    vector<bool> v(n); // Lo usaremos para guardar que vertices hay que usar para hacer todas las combinaciones posibles de subconjuntos
    backtracking(v, S, G, 0, n, n, r);
    printNewSol(S);
}
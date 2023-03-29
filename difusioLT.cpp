#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// estructura de graf
typedef vector<vector<int>> graf;

void lectura_graf (graf &g) {
    int m;
    cin >> m; // nº d'arestes
    for (int i = 0; i < m; ++i) {
        int x, y; // x i y son arestes 
        cin >> x >> y; // llegim nodes que fan aresta
        g[x].push_back(y);
        g[y].push_back(x);

    }
}

void lectura_subconj (vector<int> &s) {
    int v; // index dels vertexs del subconjunt S
    cout << "Introdueix subconjunt:\n";
    while (cin >> v) {
        s.push_back(v);
    }
}

int main () {

    int n; // nº de vertexs
    cin >> n;
    graf g(n); // graf de tamany n
    lectura_graf(g); // llegim el graf
    //int w;
    cout << "El pes per les arestes es 1\n";
    //cin >> w;
    float r; // llindar de difusio
    cout << "Introdueix un llindar entre [0.0, 1.0]:\n";
    cin >> r;
    vector<int> s;
    lectura_subconj(s);
    vector<bool> influenciat(n, false);

//  Fins aqui ha estat lectura d'entrada -------------------------------------------------------

    int m = s.size(); // iteracions minimes a fer, ja que es el subconjunt inicial
    int t = 0; // t es el numero de "torns" transcorreguts
    bool canvi = false;
    for (int i = 0; i < m; ++i) {
        int adj = g[s[i]].size(); // preparem un for que mirara totes les adjacencias a las que es podra influenciar
        for (int j = 0; j < adj; ++j) {
            int a = g[s[i]][j]; // com que s'utilitza mes d'una vegada ho guardem per a que sigui mes comode
            if (influenciat[a] == false and 1 > (r*a*180/M_PI)) { // comprovem que no estiguem revisant un vertex ja influenciat i que w de ij sigui superior al llindar de j
                s.push_back(a); // afegim el vertex al conjunt d'influenciats
                influenciat[a] = true;
                canvi = true; // marquem que hi ha un canvi en el conjunt d'influenciats
                ++m;
                }
            }
            
            if (canvi) { // t augmenta nomes quan s'ha influenciat a algu en un torn, aqui controlem que aixo passi
                ++t;
                canvi = false;
            }
            influenciat[s[i]] = true;

    }
    sort(s.begin(), s.end()); // No fa falta que estigui ordenat, es per estetica
    cout << "Conjunt influenciat = {";
    for (int i = 0; i < m-1; ++i) {
        cout << s[i] << ", ";
    }
    cout << s[m-1] << '}' << endl;
    cout << "t = " << t << endl;
}
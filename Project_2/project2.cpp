//Project 2

#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Vertice {
    int color; // 0 - Branco , 1 - Cinzento, 2 - Preto
    int value;
    int tempoInicio;
    int tempoFim;
    list<Vertice> verticesAdjacentes;
};

void DFS(vector<Vertice> grafo) {
    
}





int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int n, m, x ,y;
    cin >> n >> m;

    vector<Vertice> grafo(n+1);  //grafo representado por uma lista de adjacencias

    for(int i = 1; i <=n ; i++) 
        grafo[i].value = i;
    
    for(int i = 0; i < m; i++) {
        cin >> x >> y;

        Vertice verticeY;
        verticeY.value = y;
        verticeY.color = 0;
        
        grafo[x].verticesAdjacentes.push_back(verticeY);
    }

    return 0;
}
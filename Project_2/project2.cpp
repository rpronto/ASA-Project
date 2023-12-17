//Project 2

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

struct Vertice {
    int cor; // 0 - Branco , 1 - Cinzento, 2 - Preto
    int valor;
    int tempoInicio;
    int tempoFim;
    int r; // numero de saltos maximo ate ao primeiro elemento de ordem topologica inversa
    list<int> verticesAdjacentes;
};

int DFS_Visit(vector<Vertice> &grafo, Vertice vertice, int tempo) {
    stack<Vertice> pilha;
    pilha.push(vertice);
    grafo[vertice.valor].cor = 1;
    tempo ++;
    grafo[vertice.valor].tempoInicio = tempo;
    while(!pilha.empty()) {
        for(int verticeAdj: pilha.top().verticesAdjacentes) {
            if(grafo[verticeAdj].cor == 0) 
                pilha.push(grafo[verticeAdj]);
        }
        if(grafo[pilha.top().valor].cor == 0) {
            grafo[pilha.top().valor].cor = 1;
            tempo++;
            grafo[pilha.top().valor].tempoInicio = tempo;
            continue;
        }
        if(grafo[pilha.top().valor].cor == 1) {
            grafo[pilha.top().valor].cor = 2;
            tempo++;
            grafo[pilha.top().valor].tempoFim = tempo;
            pilha.pop();
            continue;
        }
        pilha.pop();   
    }
    return tempo;
}

void DFS(vector<Vertice> &grafo) {
    int tempo = 0;
    for(Vertice &vertice: grafo) {
        if(vertice.cor == 0)
            tempo = DFS_Visit(grafo, vertice, tempo);
    }
}

void getGrafoT(vector<Vertice> &grafo, vector<Vertice> &grafoT) {
    for(Vertice vertice : grafo) {
        grafoT[vertice.valor].valor = vertice.valor;
        for(int verticeAdj : vertice.verticesAdjacentes) {
            Vertice verticeT;
            verticeT.valor = vertice.valor;
            grafoT[verticeAdj].verticesAdjacentes.push_back(verticeT.valor);
        }
    }
}

int getResult(vector<Vertice> &grafoT, vector<Vertice> &ordemTop) {
    int first = ordemTop[0].valor;
    int res = 0;
    for(Vertice vertice : grafoT) 
        vertice.r = 0;
    ordemTop.pop_back(); //retira o ultimo elemento que sera o de indice 0
    for(Vertice vertice : ordemTop) {
        int max_r = 0;
        for(int verticeAdj : grafoT[vertice.valor].verticesAdjacentes) {
            if((verticeAdj == first) && (max_r < 1)) 
                max_r = 1;
            if(grafoT[verticeAdj].r >= max_r)
                max_r = grafoT[verticeAdj].r + 1;  
        }
        grafoT[vertice.valor].r = max_r;
        if(max_r != 0)
            res = vertice.valor; 
    }
    
    return grafoT[res].r;  
}


bool compareFinalTime(const Vertice &v1, const Vertice &v2) {
    return v1.tempoFim > v2.tempoFim;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int n, m, x ,y;
    cin >> n >> m;

    vector<Vertice> grafo(n+1);  //grafo representado por uma lista de adjacencias
    grafo[0].cor = -1;
    for(int i = 1; i <=n ; i++) {
        grafo[i].valor = i;
        grafo[i].cor = 0;
        grafo[i].tempoInicio = 0;
        grafo[i].tempoFim = 0;
    }
    
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        grafo[x].verticesAdjacentes.push_back(y);
    }

    DFS(grafo);
    sort(grafo.begin(), grafo.end(), compareFinalTime);
    
    vector<Vertice> grafoTrans(n+1); // grafo ordenado por ordem topologica inversa
    getGrafoT(grafo, grafoTrans);
    
    
    cout << getResult(grafoTrans, grafo) << "\n";
    
    
    
    /*
    cout << "\n" << grafoTrans[0].r << "\n" << grafoTrans[1].r << "\n" << grafoTrans[6].r;
    for(Vertice vertice:grafoTrans) {
        cout << vertice.valor << " " << vertice.tempoFim << " ";
        for(Vertice verticeAdj:vertice.verticesAdjacentes) {
            cout << verticeAdj.valor << " ";
        }
        cout << "\n";
    }
    }*/

    return 0;
}
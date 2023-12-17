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
    int SCCFlag;
    vector<int> verticesAdjacentes;
};

int DFS_Visit(vector<Vertice> &grafo, Vertice vertice, int tempo, int SCCFlag) {
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
            grafo[pilha.top().valor].SCCFlag = SCCFlag;
            pilha.pop();
            continue;
        }
        pilha.pop();   
    }

    return tempo;
}

void DFS(vector<Vertice> &grafo, vector<int> ordem, int DFSNumber) {
    int tempo = 0;
    int SCCFlag = 0;
    for(size_t i = 0; i < grafo.size(); i++) {
        if(grafo[ordem[i]].cor == 0) {
            if(DFSNumber == 2)
                SCCFlag++;
            tempo = DFS_Visit(grafo, grafo[ordem[i]], tempo, SCCFlag);
        }

    }
}

void getGrafoT(vector<Vertice> &grafo, vector<Vertice> &grafoT) {
    for(Vertice vertice : grafo) {
        grafoT[vertice.valor].valor = vertice.valor;
        grafoT[vertice.valor].tempoInicio = vertice.tempoInicio;
        grafoT[vertice.valor].tempoFim = vertice.tempoFim;
        grafoT[vertice.valor].r = vertice.r;
        grafoT[vertice.valor].SCCFlag = 0;
        if(vertice.valor == 0)
            grafoT[vertice.valor].cor = -1;
        for(int verticeAdj : vertice.verticesAdjacentes) {
            int verticeT;
            verticeT = vertice.valor;
            grafoT[verticeAdj].verticesAdjacentes.push_back(verticeT);
        }
    }
}

int getResult(vector<Vertice> &grafoT, vector<int> &ordemTop) {
    int first = ordemTop[0];
    int res = 0;
    for(Vertice vertice : grafoT) 
        vertice.r = 0;
    
    for(size_t i = 0; i < ordemTop.size(); i++) {
        int max_r = 0;
        for(int verticeAdj : grafoT[ordemTop[i]].verticesAdjacentes) {
            if((verticeAdj == first) && (max_r < 1)) 
                max_r = 1;
            if(grafoT[verticeAdj].r > max_r){
                if((grafoT[verticeAdj].SCCFlag == grafoT[ordemTop[i]].SCCFlag)) {
                    max_r = grafoT[verticeAdj].r;
                } else {
                    max_r = grafoT[verticeAdj].r + 1;  
                }
            }
        }
        grafoT[ordemTop[i]].r = max_r;
        if(max_r != 0)
            res = grafoT[ordemTop[i]].valor; 
    }
    
    return grafoT[res].r;  
}

bool compareFinalTime(const Vertice &v1, const Vertice &v2) {
    return v1.tempoFim > v2.tempoFim;
}

bool compareValor(const Vertice &v1, const Vertice &v2) {
    return v1.valor < v2.valor;
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
        grafo[i].r = 0;
    }
    
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        grafo[x].verticesAdjacentes.push_back(y);
    }

    vector<int> ordemCrescente(n+1);
    for(int i = 0; i <= n; i++){ 
        ordemCrescente[i] = i;
        
    }
    DFS(grafo, ordemCrescente, 1);
       
    vector<Vertice> grafoTrans(n+1); 
    getGrafoT(grafo, grafoTrans);
    sort(grafoTrans.begin(), grafoTrans.end(), compareFinalTime);
    vector<int> ordemTopInv(n+1);
    for(int i = 0; i <= n; i++) {
        ordemTopInv[i] = grafoTrans[i].valor;   
    }
    ordemTopInv.pop_back(); //retira o ultimo elemento que sera o de indice 0
    sort(grafoTrans.begin(), grafoTrans.end(), compareValor);
    DFS(grafoTrans, ordemTopInv, 2);
    
    cout << getResult(grafoTrans, ordemTopInv) << "\n";

    return 0;
}
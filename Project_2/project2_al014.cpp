//Project2 - al014 , ist1106819 , ist1105672

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

struct Vertice {
    int color; // 0 - Branco , 1 - Cinzento, 2 - Preto
    int value;
    int beginTime;
    int endTime;
    int maxJ; // numero maximo de saltos ate ao primeiro elemento de ordem topologica inversa
    int sccFlag; // identifca a que SCC pertence
    vector<int> adjVertices;
};

int DFS_Visit(vector<Vertice> &graph, Vertice vertice, int time, int sccFlag) {
    stack<Vertice> stack;
    stack.push(vertice);
    while(!stack.empty()) {
        if(graph[stack.top().value].color == 0) {
            graph[stack.top().value].color = 1;
            time++;
            graph[stack.top().value].beginTime = time;  
        }
        for(int verticeAdj: stack.top().adjVertices) {
            if(graph[verticeAdj].color == 0) 
                stack.push(graph[verticeAdj]);
        }
        if(graph[stack.top().value].color == 0) {
            graph[stack.top().value].color = 1;
            time++;
            graph[stack.top().value].beginTime = time;
            continue;  
        }
        if(graph[stack.top().value].color == 1) {
            graph[stack.top().value].color = 2;
            time++;
            graph[stack.top().value].endTime = time;
            graph[stack.top().value].sccFlag = sccFlag;
            stack.pop();
            continue;
        }
        stack.pop();   
    }

    return time;
}

void DFS(vector<Vertice> &graph, vector<int> order, int dfsFlag) {
    int time = 0;
    int sccFlag = 0;
    for(size_t i = 0; i < order.size(); i++) {
        if(graph[order[i]].color == 0) {
            if(dfsFlag == 2)
                sccFlag++;
            time = DFS_Visit(graph, graph[order[i]], time, sccFlag);
        }
    }
}

void getgraphT(vector<Vertice> &graph, vector<Vertice> &graphT) {
    for(Vertice vertice : graph) {
        graphT[vertice.value].value = vertice.value;
        graphT[vertice.value].beginTime = vertice.beginTime;
        graphT[vertice.value].endTime = vertice.endTime;
        graphT[vertice.value].maxJ = vertice.maxJ;
        graphT[vertice.value].sccFlag = 0;
        if(vertice.value == 0)
            graphT[vertice.value].color = -1;
        for(int verticeAdj : vertice.adjVertices) {
            int verticeT;
            verticeT = vertice.value;
            graphT[verticeAdj].adjVertices.push_back(verticeT);
        }
    }
}

int getResult(vector<Vertice> &graphT, vector<int> &topologicalOrder) {
    int first = topologicalOrder[0];
    int biggestMaxJ = 0;
    int biggestSccMaxJ = 0;
    int currentSccFlag = 0;
    for(Vertice vertice : graphT) 
        vertice.maxJ = 0;
    for(size_t i = 0; i < topologicalOrder.size(); i++) {
        int maxJ = 0;
        for(int verticeAdj : graphT[topologicalOrder[i]].adjVertices) {
            if(graphT[verticeAdj].sccFlag == graphT[topologicalOrder[i]].sccFlag) // se pertencer a um SCC com mais de 1 elemento identifica o SCC
                currentSccFlag = graphT[topologicalOrder[i]].sccFlag;
            if((graphT[verticeAdj].sccFlag == currentSccFlag) && (graphT[verticeAdj].maxJ < biggestSccMaxJ)) // se pertence a um SCC e nao tem maxJ igual a sua SCC atualiza-se o seu maxJ
                graphT[verticeAdj].maxJ = biggestSccMaxJ;
            if((verticeAdj == first) && (maxJ < 1) && (graphT[topologicalOrder[i]].sccFlag != graphT[first].sccFlag))  // se tem como vertice adjacente o primeiro elemento de topologicalOrder
                maxJ = 1;                                                                                              // e nao pertencem a mesma SCC atualiza maxJ a 1
            if(graphT[verticeAdj].maxJ >= maxJ){    
                if(graphT[verticeAdj].sccFlag == graphT[topologicalOrder[i]].sccFlag)   // se pertence a mesma SCC que um vertice adjacente e maxJ do vertice adjacente eh maior que o maxJ
                    maxJ = graphT[verticeAdj].maxJ;                                     // atual, atualiza o maxJ atual
                else 
                    maxJ = graphT[verticeAdj].maxJ + 1;                                 // caso contrario maxJ atual eh igual ao maxJ do vertice adjacente + 1
            }
        }
        graphT[topologicalOrder[i]].maxJ = maxJ;
        if(currentSccFlag == graphT[topologicalOrder[i]].sccFlag) { //
            if(maxJ > biggestSccMaxJ)
                biggestSccMaxJ = maxJ;  // atualiza o biggestSccMaxJ com o maior maxJ dessa SCC de forma a poder atualizar os restantes vertices da SCC mais tarde 
        }
        if(maxJ > biggestMaxJ)
            biggestMaxJ = maxJ;   
    }
    return biggestMaxJ;  // retorna o maior maxj do grafo
}

bool compareFinalTime(const Vertice &v1, const Vertice &v2) {
    return v1.endTime > v2.endTime;
}

bool compareValue(const Vertice &v1, const Vertice &v2) {
    return v1.value < v2.value;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int n, m, x ,y;
    cin >> n >> m;

    if ( (n == 0) || (m == 0)) {
        cout << 0 << "\n";
        return 0;
    }

    vector<Vertice> graph(n+1); // grafo representado como uma lista de adjacencias
    graph[0].color = -1;        // nao eh utilizado o indice zero e marca-se a cor como -1 para nao ter interferencia

    for(int i = 1; i <=n ; i++) {
        graph[i].value = i;
        graph[i].color = 0;
        graph[i].beginTime = 0;
        graph[i].endTime = 0;
        graph[i].maxJ = 0;
    }
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        graph[x].adjVertices.push_back(y);
    }
    vector<int> ascendingOrder(n+1);
    for(int i = 0; i <= n; i++)
        ascendingOrder[i] = i;
        
    DFS(graph, ascendingOrder, 1);

    vector<Vertice> graphTrans(n+1);
    getgraphT(graph, graphTrans);
    sort(graphTrans.begin(), graphTrans.end(), compareFinalTime);

    vector<int> topologicalOrderInv(n+1);
    for(int i = 0; i <= n; i++) 
        topologicalOrderInv[i] = graphTrans[i].value;  
    topologicalOrderInv.pop_back(); // retira o ultimo elemento que sera o de indice 0

    sort(graphTrans.begin(), graphTrans.end(), compareValue);
    
    DFS(graphTrans, topologicalOrderInv, 2);

    cout << getResult(graphTrans, topologicalOrderInv) << "\n";
    return 0;
}
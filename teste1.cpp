//Project1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int x;
    int y;
    int v;
};


int  cut (int X, int Y, vector<Piece>& pieces, int n) {
    vector<vector<int>> k(X+1, vector<int>(Y+1, 0));
    
    for(int i = 1; i <= n; i++){
        for(int x = 1; x <= X; x++) {
            for(int y = 1; y <= Y; y++) {
                if(((pieces[i].x > x) || (pieces[i].y > y)) && ((pieces[i].x > y) || (pieces[i].y > x))){
                        k[x][y] = k[x][y];
                        continue;
                }
                if(((pieces[i].x <= x) && (pieces[i].y <= y)) || ((pieces[i].x <= y) && (pieces[i].y <= x))) {
                    int normal = 0;
                    int flip = 0;
                    if((pieces[i].x <= x) && (pieces[i].y <= y)) {
                        int temp1 =  max(k[x][y],
                        pieces[i].v + k[x - pieces[i].x][y] + k[pieces[i].x][y - pieces[i].y]);
                        int temp2 =  max(k[x][y],
                        pieces[i].v + k[x][y - pieces[i].y] +  k[x - pieces[i].x][pieces[i].y]);
                        normal = max(temp1,temp2);
                    } if((pieces[i].y <= x) && (pieces[i].x <= y)) {
                        int aux = pieces[i].x;
                        pieces[i].x = pieces[i].y;
                        pieces[i].y = aux;
                        int temp1 =  max(k[x][y],
                        pieces[i].v + k[x - pieces[i].x][y] + k[pieces[i].x][y - pieces[i].y]);
                        int temp2 =  max(k[x][y],
                        pieces[i].v + k[x][y - pieces[i].y] +  k[x - pieces[i].x][pieces[i].y]);
                        flip = max(temp1,temp2);
                    } 
                    k[x][y] = max(normal, flip);
                }
            }
        }
    }
    return k[X][Y];
}

bool comparePieces(const Piece &a, const Piece &b) {
    if(a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

int main() {
    int x, y, n;
    cin >> x >> y;
    cin >> n;

    vector<Piece> pieces(n+1);
    
    pieces[0].x = 0;
    pieces[0].y = 0;
    pieces[0].v = 0;
    

    for (int i = 1; i <= n; i++)
        cin >> pieces[i].x >> pieces[i].y >> pieces[i].v;
 
    // Ordenação com base em x e depois em y
    sort(pieces.begin(), pieces.end(), comparePieces);

    int res = cut(x, y, pieces, n);
    cout << res << endl;

    return 0;
}
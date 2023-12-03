//Project1

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Piece {
    int x;
    int y;
    int v;
};

int  cut (int X, int Y, vector<Piece>& pieces, int n) {
    vector<vector<int>> k(X+1, vector<int>(Y+1, 0));
    
    for (int i = 1; i <= n; i++) {
        if (pieces[i].x <= X && pieces[i].y <= Y) {
            k[pieces[i].x][pieces[i].y] = pieces[i].v;
            if (pieces[i].y <= X) {k[pieces[i].y][pieces[i].x] = pieces[i].v;}
        }
    }
    for(int x = pieces[1].x; x <= X; x++) {
        for(int y = x; y <= Y; y++) {
            for (int cut_x = 1; cut_x <= x/2; cut_x++) {
                k[x][y] = max(k[x][y], k[cut_x][y] + k[x - cut_x][y]);
            }
            for (int cut_y = 1; cut_y <= y/2; cut_y++) {
                k[x][y] = max(k[x][y], k[x][cut_y] + k[x][y - cut_y]);
            }
            if (y <= X) {k[y][x] = k[x][y];}
        }
    }
    return k[X][Y];
}

bool comparePieces(const Piece &a, const Piece &b) {
    if(a.x == b.x) {
        if (a.y == b.y) {
            return a.v < b.v;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}

int main() {

    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int x, y, n;
    cin >> x >> y;
    cin >> n;
    vector<Piece> pieces(n+1, {0,0,0});
    
    for (int i = 1; i <= n; i++) {
        cin >> pieces[i].x >> pieces[i].y >> pieces[i].v;
        if (pieces[i].x > pieces[i].y) {
            swap(pieces[i].x, pieces[i].y);
        }
    }

    // Ordenação com base em x e depois em y
    sort(pieces.begin(), pieces.end(), comparePieces);
    if (x > y) {
        swap(x,y);
    }
    int res = cut(x, y, pieces, n);
    cout << res << "\n";
    return 0;
}
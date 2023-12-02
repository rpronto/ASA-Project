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
    
    int i = 1;
    for(int x = 1; x <= X; x++) {
        for(int y = x; y <= Y; y++) {
            int val = 0, max_x = 0, max_y = 0;
            if ((i <= n) && (((pieces[i].x == x) && (pieces[i].y == y)) || ((pieces[i].x == y) && (pieces[i].y == x)))) {
                  val = pieces[i].v;
                  i++;
            }
            for (int cut_x = 1; cut_x <= ceil(x/2); cut_x++) {
                int aux = k[cut_x][y] + k[x - cut_x][y];
                max_x = max(max_x, aux);
            }
            for (int cut_y = 1; cut_y <= ceil(y/2); cut_y++) {
                int aux = k[x][cut_y] + k[x][y - cut_y];
                max_y = max(max_y, aux);
            }
            k[x][y] = max({val, max_x, max_y});
            if (y <= X) {k[y][x] = k[x][y];}
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
    if (x > y) {
        int aux = x;
        x = y;
        y = aux;
    }
    int res = cut(x, y, pieces, n);
    cout << res << endl;
    return 0;
}
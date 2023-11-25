//Project1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int  cut (int X, int Y, vector<int>& piece_x, vector<int>& piece_y, vector<int>& v, int n) {
    
    vector<vector<vector<int>>> k(X+1, vector<vector<int>>(Y+1, vector<int>(n+1, 0)));
    for (int x = 1; x <= X; x++) {
        for(int y = 1; y <= Y; y++ ) {
            for(int i = 1; i <= n; i++) {
                if(piece_x[i] <= x && piece_y[i] <= y) {
                    k[x][y][i] =  max(k[x][y][i-1],
                    v[i] + k[x - piece_x[i]][y][i] + k[piece_x[i]][piece_y[i]][i] + 
                    k[piece_x[i]][y - piece_y[i]][i]);
                } else if(piece_y[i] <= y) {
                    k[x][y][i] =  max(k[x][y][i-1],
                    v[i] + k[x][y - piece_y[i]][i] + k[piece_x[i]][piece_y[i]][i] + 
                    k[x - piece_x[i]][piece_y[i]][i]);
                } else if((piece_y[i] <= x) && (piece_x[i] <= y)) {
                    k[x][y][i] = max({k[x][y][i-1],
                    v[i] + k[x - piece_y[i]][y][i] + k[piece_y[i]][piece_x[i]][i] + 
                    k[piece_y[i]][y - piece_x[i]][i],
                    v[i] + k[x][y - piece_x[i]][i] + k[piece_y[i]][piece_x[i]][i] + 
                    k[x - piece_y[i]][piece_x[i]][i]
                    });
                } else {
                    k[x][y][i] = k[x][y][i-1];
                }
            }
        }
    }
    return k[X][Y][n];
}

int main() {
    int x, y, n;
    cin >> x >> y;
    cin >> n;

    vector<int> piece_x(n + 1), piece_y(n + 1), v(n + 1);
    piece_x[0] = 0;
    piece_y[0] = 0;
    v[0] = 0;
    

    for (int i = 1; i <= n; i++)
        cin >> piece_x[i] >> piece_y[i] >> v[i];
 
    int res = cut(x, y, piece_x, piece_y, v, n);
    cout << res << endl;

    return 0;
}
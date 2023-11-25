//Project1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int  chapa (int X, int Y, vector<int>& piece_x, vector<int>& piece_y, vector<int>& v, int n) {
    
    vector<vector<vector<int>>> k(X+1, vector<vector<int>>(Y+1, vector<int>(n+1, 0)));
    
    for (int x = 0; x <= X; x++) {
        for(int y = 0; y <= Y; y++ ) {
            for(int i = 0; i <= n; i++) {
                if((x == 0) || (y == 0) || (i == 0))
                    k[x][y][i] = 0;
                else if(piece_x[i] <= x) {
                    k[x][y][i] =  max(chapa(X, Y, piece_x, piece_y, v, n - 1),
                    v[i] + chapa(X - piece_x[i], Y, piece_x, piece_y, v, i) + chapa(piece_x[i], piece_y[i], piece_x, piece_y, v, i) + 
                    chapa(piece_x[i], Y - piece_y[i], piece_x, piece_y, v, i));
                } else if(piece_y[i] <= y) {
                    k[x][y][i] =  max(chapa(X, Y, piece_x, piece_y, v, n - 1),
                    v[i] + chapa(X, Y - piece_y[i], piece_x, piece_y, v, i) + chapa(piece_x[i], piece_y[i], piece_x, piece_y, v, i) + 
                    chapa(X - piece_x[i], piece_y[i], piece_x, piece_y, v, i));
                } else if((piece_y[i] <= x) && (piece_x[i] <= y)) {
                    k[x][y][i] = max({chapa(X, Y, piece_x, piece_y, v, n - 1),
                    v[i] + chapa(X - piece_y[i], Y, piece_x, piece_y, v, i) + chapa(piece_y[i], piece_x[i], piece_x, piece_y, v, i) + 
                    chapa(piece_y[i], Y - piece_x[i], piece_x, piece_y, v, i),
                    v[i] + chapa(X, Y - piece_x[i], piece_x, piece_y, v, i) + chapa(piece_y[i], piece_x[i], piece_x, piece_y, v, i) + 
                    chapa(X - piece_y[i], piece_x[i], piece_x, piece_y, v, i)
                    });
                } else {
                    k[x][y][i] = chapa(X, Y, piece_x, piece_y, v, n - 1);
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
 
    int res = chapa(x, y, piece_x, piece_y, v, n);
    cout << res << endl;

    return 0;
}
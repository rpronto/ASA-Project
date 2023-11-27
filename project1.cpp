//Project1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int  cut (int X, int Y, vector<int>& piece_x, vector<int>& piece_y, vector<int>& v, int n) {
    vector<vector<int>> k(X+1, vector<int>(Y+1, 0));
    for (int i = 1; i <= n; i++) {
        for(int x = 1; x <= X; x++) {
            for(int y = 1; y <= Y; y++) {
                if(((piece_x[i] > x) || (piece_y[i] > y)) && ((piece_x[i] > y) || (piece_y[i] > x))){
                    k[x][y] = k[x][y];
                    continue;
                } 
                int normal = 0;
                int flip = 0;
                if((piece_x[i] <= x) && (piece_y[i] <= y)) {
                    int temp1 =  max(k[x][y],
                    v[i] + k[x - piece_x[i]][y] + k[piece_x[i]][y - piece_y[i]]);
                    int temp2 =  max(k[x][y],
                    v[i] + k[x][y - piece_y[i]] +  k[x - piece_x[i]][piece_y[i]]);
                    normal = max(temp1,temp2);
                } if((piece_y[i] <= x) && (piece_x[i] <= y)) {
                    int aux = piece_x[i];
                    piece_x[i] = piece_y[i];
                    piece_y[i] = aux;
                    int temp1 =  max(k[x][y],
                    v[i] + k[x - piece_x[i]][y] + k[piece_x[i]][y - piece_y[i]]);
                    int temp2 =  max(k[x][y],
                    v[i] + k[x][y - piece_y[i]] +  k[x - piece_x[i]][piece_y[i]]);
                    flip = max(temp1,temp2);
                } 
                k[x][y] = max(normal, flip);
            }
        }
    }
    return k[X][Y];
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
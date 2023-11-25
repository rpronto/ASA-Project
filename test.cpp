#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int chapa(int X, int Y, vector<int>& x, vector<int>& y, vector<int>& v, int i) {
    
    int finalmax = 0;
    if ((X < 1) || (Y < 1) || (i < 1)) {
        return finalmax;
    }
    else if (((x[i] > X) || (y[i] > Y))) {
        // Peça não cabe, chama recursivamente sem a peça
        finalmax = chapa(X, Y, x, y, v, i - 1);
        
    } else if (x[i] <= X) {
        // Peça cabe na largura, escolhe a melhor entre com e sem a peça
        finalmax = max(chapa(X, Y, x, y, v, i - 1),
            v[i] + chapa(X - x[i], Y, x, y, v, i) + chapa(x[i], y[i], x, y, v, i) + chapa(x[i], Y - y[i], x, y, v, i));
    } else if (y[i] <= Y) {
        // Peça cabe na altura, escolhe a melhor entre com e sem a peça
        finalmax = max(chapa(X, Y, x, y, v, i - 1),
            v[i] + chapa(X, Y - y[i], x, y, v, i) + chapa(x[i], y[i], x, y, v, i) + chapa(X - x[i], y[i], x, y, v, i));
    } else if ((y[i] <= X) && (x[i] <= Y)) {
        // Peça cabe girada, escolhe a melhor entre com e sem a peça girada
        int tempmax1 = max(chapa(y[i], x[i], x, y, v, i - 1),
            v[i] + chapa(X - y[i], Y, x, y, v, i) + chapa(y[i], x[i], x, y, v, i) + chapa(y[i], Y - x[i], x, y, v, i));

        int tempmax2 = max(chapa(y[i], x[i], x, y, v, i - 1),
            v[i] + chapa(X, Y - x[i], x, y, v, i) + chapa(y[i], x[i], x, y, v, i) + chapa(X - y[i], x[i], x, y, v, i));

        finalmax = max(tempmax1, tempmax2);
    }

    return finalmax;
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


#include <iostream>
#include <algorithm>
using namespace std;

int chapa(int X, int Y, int x[], int y[], int v[], int i) {

    if (X < 1 || Y < 1 || i < 0) {
        return 0;
    }

    else if ((x[i] > X || y[i] > Y) && (y[i] > X || x[i] > Y)) {
        cout << X << " " << Y << "\n";
        return chapa(X, Y, x, y, v, i-1);
    }

    else if (y[i] <= X && x[i] <= Y) {
        cout << X << " " << Y << "\n";
        return chapa(Y, X, x, y, v, i);
    }

    else if (X >= x[i]){
        cout << X << " " << Y << "\n";
        return max(
            chapa(X, Y, x, y, v, i-1), v[i] + chapa(X - x[i], Y, x, y, v, i) + 
            chapa(x[i], y[i], x, y, v, i) + chapa(x[i], Y-y[i], x, y, v, i)
        );
    }

    else{
        cout << X << " " << Y << "\n";
        return max(
            chapa(X, Y, x, y, v, i-1), v[i] + chapa(X, Y- y[i], x, y, v, i) + 
            chapa(x[i], y[i], x, y, v, i) + chapa(X - x[i], Y, x, y, v, i)
        );
    }
}

int main() {
    int x, y, n;
    cin >> x >> y;
    cin >> n;
    int piece_x[n], piece_y[n], v[n];
    for(int i = 0; i < n; i++)
        cin >> piece_x[i] >> piece_y[i] >> v[i];

    int res = chapa(x, y, piece_x, piece_y, v, n);
    std::cout << "" << res;
    return 0;
}


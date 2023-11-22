#include <iostream>
#include <algorithm>
using namespace std;

int chapa(int X, int Y, int x[], int y[], int v[], int i) {

    if (X == 0 || Y == 0 || i < 0) {
        std::cout << "Based\n";
        return 0;
    }

    if (x[i] > X || y[i] > Y) {
        std::cout << X << " " << Y << "\n";
        std::cout << x[i] << " " << y[i] << "\n";
        std::cout << "Second\n";
        return chapa(X, Y, x, y, v, i-1);
    }

    else {std::cout << X << " " << Y << "\n"; std::cout << x[i] << " " << y[i] << "\n"; std::cout << "Normal\n";
        return max(
        chapa(X, Y, x, y, v, i-1), chapa(X-x[i], Y-y[i], x, y, v, i)
    ) + v[i];}
}

int main() {
    int x[2] = {6, 1};
    int y[2] = {3, 2};
    int v[2] = {130, 5};
    int res = chapa(7, 4, x, y, v, 1);
    std::cout << "" << res;
    return 0;
}


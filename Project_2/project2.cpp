//Project 2

#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int n, m, x ,y;
    cin >> n >> m;

    vector<list<int>> listAdj(n+1);

    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        listAdj[x].push_back(y);
    }

   
    return 0;
}
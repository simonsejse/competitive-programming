// https://open.kattis.com/problems/umferd
#include <bits/stdc++.h>
using namespace std;


int main() {

    int m, n, sum;
    sum = 0;
    char c;
    cin >> m >> n;



    while (cin >> c) {
        if (c == '.') {
            sum++;
        }
    
    }
    cout << (double) sum/(m*n);




    return 0;
}
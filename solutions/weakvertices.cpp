// https://open.kattis.com/problems/weakvertices
#include <bits/stdc++.h>
using namespace std;



void solve(int n, vector<vector<int>> v, int i) {
    vector<int> ones;
    for (int j = 0; j < n; j++) {
        if (v[i][j] == 1) ones.push_back(j);
    }

    int N = ones.size();
    for (int j = 0; j < N; j++) {
        for (int k = j+1; k < N; k++) {
            if (v[ones[j]][ones[k]] == 1) return;
        }
    }
    cout << i << " ";
    return;
}



int main() {
    int n, tmp;
    for (cin >> n; n != -1; cin >> n) {
        vector<vector<int>> v;
        // cout << "n: " << n << endl;
        for (int i = 0; i < n; i++) {
            vector<int> v1;
            for (int j = 0; j < n; j++) {
                cin >> tmp;
                v1.push_back(tmp);
            }
            v.push_back(v1);
        }
        for (int i = 0; i < n; i++) {
            solve(n, v, i);
        }
        cout << "" << endl;
        

    }


    return 0;
}

// https://open.kattis.com/problems/irepeatmyself
#include <bits/stdc++.h>
#include <string>
using namespace std;



int repeating(string s, int k) {
    if (k >= s.length()) return k;
    int siz = s.length();

    


    for (int i = k; i < siz; i+=k) {
        string s1, s2;
        if (i+k < siz) {
            s1 = s.substr(0, k);   
        } else {
            s1 = s.substr(0, siz-i);
        }
        s2 = s.substr(i, k);

        if (s1.compare(s2) == 0) {
            continue;
        } 
        else { 
            return repeating(s, k+1);
        }
    }

    return k;
}


int main() {

    int n;
    cin >> n;

    string str;
    getline(cin, str);

    while (getline(cin, str)) {
        cout << repeating(str, 1) << '\n';
        // cout << str << '\n';
    }





    return 0;
}
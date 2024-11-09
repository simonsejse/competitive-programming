// g++ -o main  .cpp && ./main
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <map>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long      ll;
typedef pair<int, int> pii;
typedef pair<ll, ll>   pll;
typedef vector<int>    vi;
typedef vector<ll>     vl;

int main() {
  int n;
  cin >> n;
  int    cnt = 0;
  string s;
  if (n % 2 == 1) {
    n -= 3;
    cnt++;
    s += "3 ";
  }
  for (int i = 0; i < (n / 2); i++) {
    s += "2 ";
    cnt++;
  }
  cout << cnt << endl;
  cout << s << endl;
  return 0;
}

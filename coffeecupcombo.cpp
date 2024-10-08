// g++ -o main template.cpp && ./main
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

  int    stay_awake = 0, n = 0, cnt = 0;
  string bin;
  cin >> n;
  cin >> bin;

  for (int i = 0; i < n; i++) {
    if (bin[i] == '1') {
      stay_awake = 2;
      cnt++;
      continue;
    }
    if (stay_awake <= 0)
      continue;

    cnt++;
    stay_awake--;
  }

  cout << cnt;

  return 0;
}
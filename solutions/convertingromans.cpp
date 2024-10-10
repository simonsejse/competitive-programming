// https://open.kattis.com/problems/convertingromans?editresubmit=14373798
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
  ll n, sum, max, val;
  cin >> n;
  string         str;
  map<char, int> roman_to_number = {{'I', 1},   {'V', 5},   {'X', 10},
                                    {'L', 50},  {'C', 100}, {'D', 500},
                                    {'M', 1000}};

  if (!(n > 0 && n <= pow(10, 3)))
    return 0;

  for (int i = 0; i < n; i++) {
    // restart roman number
    cin >> str;
    sum = 0;
    max = roman_to_number[str[str.length() - 1]];

    for (int j = str.length() - 1; j >= 0; j--) {
      val = roman_to_number[str[j]];

      if (val >= max) {
        sum += val;
        max = val;
        continue;
      }
      sum -= val;
    }
    cout << sum << endl;
  }

  return 0;
}

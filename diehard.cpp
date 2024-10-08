// https://open.kattis.com/problems/diehard?editresubmit=14374601
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

pair<int, int> get_wins(int dice_1[], int dice_2[]) {
  pair<int, int> wins = make_pair(0, 0);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (dice_1[i] == dice_2[j])
        continue;
      if (dice_1[i] > dice_2[j])
        wins.first++;
      else
        wins.second++;
    }
  }
  return wins;
}

int main() {

  int  xj;
  bool flag[3];
  int  d[3][6];
  int  wins[3];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 6; j++) {
      cin >> d[i][j];
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      pair<int, int> w = get_wins(d[i], d[j]);
      wins[i]          = w.first;
      wins[j]          = w.second;

      if (wins[i] == wins[j] && wins[i] == 0) {
        flag[0] = true;
        flag[1] = true;
        flag[2] = true;
        goto end;
      }
      if (wins[i] > wins[j]) {
        flag[j] = true;
      }
      if (wins[i] < wins[j]) {
        flag[i] = true;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    if (!flag[i]) {
      cout << i + 1 << endl;
      return 0;
    }
  }

end:
  cout << "No dice" << endl;

  return 0;
}
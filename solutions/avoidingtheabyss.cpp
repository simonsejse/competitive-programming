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
  long max_x = pow(10, 9);
  long max_y = pow(10, 9);
  long min_x = -max_x;
  long min_y = -max_y;

  int xs, ys, xp, yp, xt, yt;
  cin >> xs >> ys;
  cin >> xp >> yp;
  cin >> xt >> yt;

  int diffxs = xs - xp;
  int diffys = ys - yp;

  int diffxt = xp - xt;
  int diffyt = yp - yt;

  int            cnt = 0;
  pair<int, int> t_path[10];

  int            cnt_t = 0;
  pair<int, int> general_path[10];

  xs                  = diffxs <= 0 ? min_x : max_x;
  general_path[cnt++] = make_pair(xs, ys);

  ys                  = diffys <= 0 ? min_y : max_y;
  general_path[cnt++] = make_pair(xs, ys);

  xt              = diffxt <= 0 ? min_x : max_x;
  t_path[cnt_t++] = make_pair(xt, yt);

  yt              = diffyt <= 0 ? min_y : max_y;
  t_path[cnt_t++] = make_pair(xt, yt);

  ys                  = yt;
  general_path[cnt++] = make_pair(xs, ys);

  xs                  = xt;
  general_path[cnt++] = make_pair(xs, ys);

  for (int i = 1; i >= 0; i--) {
    general_path[cnt++] = make_pair(t_path[i].first, t_path[i].second);
  }

  cout << cnt << endl;

  for (int i = 0; i < 6; i++) {
    cout << general_path[i].first << " " << general_path[i].second << endl;
  }

  return 0;
}
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/* clang-format off */

/* 1. TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vc vector<char>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* 2. FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define fr(i,e,s) for(long long int i=e-1;i>=s;i--)
#define fop(s,i,op,e, inc) for(long long int i = s;i op e;i inc)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define T(cond, a, b) ((cond) ? (a) : (b)) // Short ternary operator
#define trav(a, x) for(auto& a : x)        // Iterate over elements of a container
#define BOUND(lb, lb_op, var, up_op, up) ((lb) lb_op (var) && (var) up_op (up)) // Bound check
#define IF(cond, stmts) do { if (cond) { stmts; } } while (0)

/* 3. MATH SHORTCUTS */
#define flr(x) floor(x)          // Shortcut for floor
#define cl(x) ceil(x)            // Shortcut for ceil

template<typename T>
std::set<T> U(const std::set<T>& a, const std::set<T>& b) {
  std::set<T> result;
  std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
  return result;
}

template<typename T>
std::set<T> I(const std::set<T>& a, const std::set<T>& b) {
  std::set<T> result;
  std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
  return result;
}

template<typename T>
std::set<T> D(const std::set<T>& a, const std::set<T>& b) {
    std::set<T> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

/* 4 CONVERSIONS */
template <typename U>
auto toset(const U& v) -> std::set<typename U::value_type> {
    return std::set<typename U::value_type>(v.begin(), v.end());
}


/* 5 PRINTS */
template <class T>
void out_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

template<typename T>
void out_s(set<T> &s) { cout << "{"; for (auto x : s) cout << x << ","; cout << "\b}"; }


/* 6. UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }

/*  7. All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
typedef string str;

/* clang-format on */
#define ONLINE_JUDGE 1

void compute_cal_proc(string unknown, double multiplier, double& tc, double& fc,
                      double& p, bool& fat_in_pct) {
  string unit   = unknown.substr(unknown.size() - 1, 1);
  ll     value  = stol(unknown.substr(0, unknown.size() - 1));
  bool   is_fat = multiplier == 9;

  if (unit == "g") {
    value *= multiplier;
    tc += value;
  } else if (unit == "C") {
    tc += value;
  } else {
    p += value;
    if (is_fat) {
      cout << "It is fat" << "and multiplier is " << multiplier << endl;
      fat_in_pct = true;
    }
  }
  if (is_fat) {
    fc += value;
  }
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);   // input.txt
  freopen("output.txt", "w", stdout); // output.txt
#endif
  string a, b, c, d, e; // fat | protein | sugar | stac | alchol
  double stop = 0, tc = 0, p = 0, fc = 0;
  bool   fat_in_pct = 0; // maybe an array because
  /* a is in pct the second time not first.
  3g 10g 10% 0g 0g
  55% 100C 0% 0g 30g
   */

  while (true) {
    cin >> a;
    if (a == "-") {
      stop++;
      if (stop > 1)
        break;
      if (p > 0) {
        double calories_per_pct = tc / (100 - p);
        calories_per_pct *= p;
        tc += calories_per_pct;

        if (fat_in_pct) {
          fc *= calories_per_pct;
          tc += fc;
        }
        cout << ceil(fc / tc * 100) << "%" << endl;
      } else {
        cout << ceil(fc / tc * 100) << "%" << endl;
      }

      p          = 0;
      fc         = 0;
      tc         = 0;
      fat_in_pct = false;
      continue;
    }
    stop = 0;
    cin >> b >> c >> d >> e;
    vector<pair<string, double>> inputs = {
        {a, 9}, {b, 4}, {c, 4}, {d, 4}, {e, 7}};

    trav(i, inputs) { compute_cal_proc(i.F, i.S, tc, fc, p, fat_in_pct); }
  }

  return 0;
}

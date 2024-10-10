#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define T(cond, a, b) ((cond) ? (a) : (b)) // Short ternary operator
#define trav(a, x) for(auto& a : x)        // Iterate over elements of a container
#define BOUND(lb, lb_op, var, up_op, up) ((lb) lb_op (var) && (var) up_op (up))

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
template <typename T>
std::set<T> vtos(const std::vector<T>& v) {
    return std::set<T>(v.begin(), v.end());
}

template <typename T>
std::set<T> ltos(const std::list<T>& l) {
    return std::set<T>(l.begin(), l.end());
}

template <typename T>
std::set<T> dtos(const std::deque<T>& d) {
    return std::set<T>(d.begin(), d.end());
}

/* 5 PRINTS */
template <class T>
void out_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }
#define out(s) cout << s << endl;

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

/**
 * @brief Main function to process the scrolling sign problem.
 *
 * This function reads input values, processes them, and outputs the results.
 * It reads the number of test cases and for each test case, it reads the number
 * of characters in the sign and the number of words. It then processes each
 * word to determine how many characters have been shifted to the left.
 *
 * For me, I found this exercise very good to think of it as sort of a sign that
 * shifts to the left. So the way that I solved the exercise is the same way. I
 * look at the sign and for each iteration, it gets shifted to the left. It
 * takes the previous sign value (e.g., "cat") and shifts it to the left, adding
 * the removed letters to the count. I don't care about what the letters are; I
 * just check how many were removed. That's why I perform the checking as shown
 * in the code.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);   // input.txt
  freopen("output.txt", "w", stdout); // output.txt
#endif
  ll n;
  cin >> n;
  if (!BOUND(1, <=, n, <=, 5)) {
    return 0;
  }
  f(i, 0, n) {
    ll C, W;
    cin >> C >> W;
    string prev_word;
    cin >> prev_word;
    ll cnt = C;
    f(j, 1, W) {
      string word;
      cin >> word;
      f(c, 0, C) {
        string sub_word      = word.substr(0, C - c);
        string sub_prev_word = prev_word.substr(c, C - c);
        if (prev_word[c] == word[0] && sub_word == sub_prev_word)
          break;
        cnt++;
      }
      prev_word = word;
    }
    cout << cnt << endl;
  }
  return 0;
}
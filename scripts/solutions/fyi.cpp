#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

#pragma region Core Library

/* clang-format off */

/* 1. TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vc vector<char>
#define vs vector<string>
#define vll vector<long long>
#define vpsi vector<pair<string, int>>
#define mii map<int, int>
#define mci map<char, int>
#define msi map<string, int>
#define mss map<string, string>
#define msl map<string, long long>
#define mls map<long long, string>
#define si set<int>
#define sc set<char>
#define ss set<string>
#define sl set<long long>
  
/* 2. FUNCTIONS */
#define ll_read(...) ll __VA_ARGS__; read(__VA_ARGS__)
#define str_read(...) string __VA_ARGS__; read(__VA_ARGS__)
#define dbl_read(...) double __VA_ARGS__; read(__VA_ARGS__)
void read() {}
template <typename T, typename... Args>
void read(T& first, Args&... args) { std::cin >> first; read(args...); }
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define fop(s,i,op,e, inc) for(long long int i = s;i op e;i inc)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define B begin()
#define E end()
#define T(cond, a, b) ((cond) ? (a) : (b)) // Short ternary operator
#define EACH(a, x) for(auto& a : x)        // Iterate over elements of a container
#define BOUND(lb, lb_op, var, up_op, up) ((lb) lb_op (var) && (var) up_op (up)) // Bound check
#define IF(cond, true_expr, false_expr) do { if (cond) { true_expr; } else { false_expr; } } while(0)

/* 3. MATH SHORTCUTS */
#if __cplusplus < 202002L
struct identity {
    template <typename T>
    constexpr T&& operator()(T&& t) const noexcept {
        return std::forward<T>(t);
    }
};
#endif
template <typename Iterator, typename Func = identity>
auto argmin(Iterator begin, Iterator end, Func func = {}) {
    auto it = std::min_element(begin, end, [&](const auto& a, const auto& b) {
        return func(a) < func(b);
    });
    return std::distance(begin, it);
}
template <typename Iterator, typename Func = identity>
auto argmax(Iterator begin, Iterator end, Func func = {}) {
    auto it = std::max_element(begin, end, [&](const auto& a, const auto& b) {
        return func(a) < func(b);
    });
    return std::distance(begin, it);
}

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
// Type trait to check if a type is a container (has begin() and end())
template <typename T, typename = void> struct is_container : std::false_type {};
template <typename T>
struct is_container<
    T, typename std::enable_if<
           !std::is_same<T, std::string>::value && // Exclude std::string
           !std::is_same<T, const char*>::value && // Exclude C-style strings
           std::is_same<decltype(std::begin(std::declval<T&>())),
                        decltype(std::end(std::declval<T&>()))>::value>::type>
    : std::true_type {};
// Base case: types that are not containers or strings
template <typename T>
typename std::enable_if<!is_container<T>::value &&
                        !std::is_same<T, std::string>::value>::type
print(const T& x) {std::cout << x;}
// Overload for strings and C-style strings
void print(const std::string& s) { std::cout << s; }
void print(const char* s) { std::cout << s; }
// Overload for pairs
template <typename T1, typename T2> void print(const std::pair<T1, T2>& p) { std::cout << "(";print(p.first); std::cout << ", "; print(p.second);std::cout << ")";}
// Overload for containers
template <typename T>
typename std::enable_if<is_container<T>::value>::type print(const T& container) { std::cout << "[";bool first = true;for (const auto& element : container) {if (!first) std::cout << ", "; print(element); first = false; } std::cout << "]"; }
template <typename T, typename... Args>
void print(const T& first, const Args&... args) { print(first); print(args...); }

/* 6. UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define NL "\n"
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

#pragma endregion

/* clang-format on */
#define ONLINE_JUDGE 1

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);   // input.txt
  freopen("output.txt", "w", stdout); // output.txt
#endif
  str_read(a);
  if (a.substr(0, 3) == "555"){
    print(1);

  } else {
    print(0);
  }
  

  return 0;
}

// https://open.kattis.com/problems/zamka
#include <bits/stdc++.h>
using namespace std;

int intCalc(int a) {
  if (a == 0)
    return 0;
  return a % 10 + intCalc(a / 10);
}

int main() {

  int l, d, x, n;
  cin >> l >> d >> x;

  for (int i = l; i <= d; i++) {
    if (intCalc(i) == x) {
      cout << i << "\n";
      break;
    }
  }

  for (int i = d; i >= l; i--) {
    if (intCalc(i) == x) {
      cout << i;
      break;
    }
  }

  return 0;
}
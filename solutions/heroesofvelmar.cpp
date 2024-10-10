// https://open.kattis.com/problems/heroesofvelmar
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
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

enum PlayerNiggas { P1, P2 };

map<string, pair<int, int>> hero_to_power_map = {};

// var1 = i, var2=n
void add_serena_powerup(int* points, int var1, int var2) {
  *points += var2 - 1;
}

void add_zenith_powerup(int* points, int var1, int var2) {
  if (var1 == 2 || var1 == 3)
    *points += 5;
}

void add_thunderheart_powerup(int* points, int var1, int var2) {
  if (var2 > 3)
    *points += 6;
}

struct Hero {
  string name;
  int    energy_cost;
  int    power_level;
  string ability;
};

vector<Hero> heroes = {
    {"Shadow", 4, 6, ""},
    {"Gale", 3, 5, ""},
    {"Ranger", 2, 4, ""},
    {"Anvil", 5, 7, ""},
    {"Vexia", 2, 3, ""},
    {"Guardian", 6, 8, ""},
    {"Thunderheart", 5, 6,
     "Phalanx - If the location this card is played at has 4 friendly cards, "
     "including this one, then its power is doubled. Note that other buffs the "
     "card receives are not doubled."},
    {"Frostwhisper", 1, 2, ""},
    {"Voidclaw", 1, 3, ""},
    {"Ironwood", 1, 3, ""},
    {"Zenith", 6, 4,
     "Centered Focus - If this card is played at the center location, +5 "
     "power."},
    {"Seraphina", 1, 1,
     "Celestial Healing - Seraphina grants +1 power to each friendly card at "
     "this location, other than itself. This includes other Seraphina cards."}};

int main() {
  std::map<std::string, void (*)(int* points, int var1, int var2)>
      add_ability_power_if_non_null;

  // Insert the function pointer correctly
  add_ability_power_if_non_null["Seraphina"]    = &add_serena_powerup;
  add_ability_power_if_non_null["Zenith"]       = &add_zenith_powerup;
  add_ability_power_if_non_null["Thunderheart"] = &add_thunderheart_powerup;

  int    n;
  string name;
  int    total_power[2] = {0};
  int    p1_points = 0, p2_points = 0, p1_wins = 0, p2_wins = 0, p1_power = 0,
      p2_power = 0;

  for (const auto& hero : heroes) {
    int ability                  = hero.ability.empty() ? -1 : 1;
    hero_to_power_map[hero.name] = make_pair(hero.power_level, ability);
  }

  int* points[2] = {&p1_points, &p2_points};

  for (int i = 0; i < 6; i++) {
    cin >> n;
    for (int j = 0; j < n; j++) {
      cin >> name;
      // 3 Seratanin Gallaktus Penis
      //
      //(i % 2 == 0 ? p1_points: p2_points) = hero_to_power_map[str]

      *points[i % 2] += hero_to_power_map[name].first;
      if (hero_to_power_map[name].second == 1)
        add_ability_power_if_non_null[name](points[i % 2], i, n);
    }
    total_power[i % 2] += *points[i % 2];

    if (i % 2 == 1) {
      if (p1_points > p2_points) {
        p1_wins++;
      } else if (p1_points < p2_points) {
        p2_wins++;
      }

      *points[0] = 0;
      *points[1] = 0;
    }
  }

  if (p1_wins > p2_wins) {
    cout << "Player 1" << endl;
  } else if (p1_wins < p2_wins) {
    cout << "Player 2" << endl;
  } else {
    if (total_power[P1] > total_power[P2]) {
      cout << "Player 1" << endl;
    } else if (total_power[P1] < total_power[P2]) {
      cout << "Player 2" << endl;
    } else {
      cout << "Tie" << endl;
    }
  }
  return 0;
}

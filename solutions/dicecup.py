#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import math
import threading
from bisect import bisect_left, bisect_right
from collections import defaultdict, deque
from functools import lru_cache
from itertools import permutations, combinations, accumulate
from heapq import heappush, heappop, heapify
from sys import stdin, stdout

# FUNCTIONS
f      = lambda s, e: range(s, e)
cf     = lambda s, e: range(s, e + 1)
rf     = lambda e, s: range(e - 1, s - 1, -1)
pb     = lambda v, x: v.append(x)
eb     = lambda v, x: v.append(x)
mp     = lambda a, b: (a, b)
F      = lambda p: p[0]
S      = lambda p: p[1]
T      = lambda cond, a, b: a if cond else b  # Short ternary operator
trav   = lambda x: (a for a in x)             # Generator expression to iterate over elements

# INPUT FUNCTIONS
inp    = lambda: int(input())
strng  = lambda: input().strip()
jn     = lambda x, l: x.join(map(str, l))
strl   = lambda: list(input().strip())
mul    = lambda: map(int, input().strip().split())
mulf   = lambda: map(float, input().strip().split())
seq    = lambda: list(map(int, input().strip().split()))

# MATH SHORTCUTS
flr    = math.floor                 # Shortcut for floor
ceil   = lambda x: int(x) if x == int(x) else int(x) + 1
ceildiv= lambda x, d: x // d if x % d == 0 else x // d + 1

# PRINTS
print_v= lambda v: print("{" + ",".join(map(str, v)) + "}")

# UTILS
MOD    = 10**9 + 7
PI     = 3.1415926535897932384626433832795

flush  = lambda: stdout.flush()
stdstr = lambda: stdin.readline()
stdint = lambda: int(stdin.readline())
stdpr  = lambda x: stdout.write(str(x))

gcd    = math.gcd  # Using math library's gcd function for efficiency

lcm    = lambda a, b: a * b // gcd(a, b)

to_upper= lambda a: a.upper()
to_lower= lambda a: a.lower()

def prime(a):
    if a <= 1:
        return False
    if a <= 3:
        return True
    if a % 2 == 0 or a % 3 == 0:
        return False
    for i in range(5, int(math.sqrt(a)) + 1, 6):
        if a % i == 0 or a % (i + 2) == 0:
            return False
    return True

yes    = lambda: print("YES")
no     = lambda: print("NO")

# All Required define Pre-Processors and typedef Constants
int32  = int
uint32 = int
int64  = int
uint64 = int

# Main function
def main():
    sys.setrecursionlimit(1 << 25)

    N, P = map(int, input().split())

    S1 = [x for x in range(1, N + 1)]
    S2 = [x for x in range(1, P + 1)]
    
    # zip 
    sample_space = [x + y for x in S1 for y in S2]
    
    probabilities = [0] * (N + P + 1) 

    for sample in sample_space:
        probabilities[sample - 1] += 1

    total_samples = len(sample_space)
    probabilities = [p / total_samples for p in probabilities]

    max_prob = max(probabilities[1:])
    best_probabilities = [i + 1 for i, prob in enumerate(probabilities) if prob == max_prob]

    for i in best_probabilities:
        print(i)  

if __name__ == "__main__":
    threading.Thread(target=main).start()

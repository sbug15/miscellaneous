import numpy as np
import itertools


def findsubsets(S, m):
    return set(itertools.combinations(S, m))

N = int(raw_input())
arr = map(int, raw_input().split(' '))

_sum = 0
for i in range(1, N + 1, 2):
    for subset in findsubsets(arr, i):
        _sum += np.median(subset)

print int(_sum) % (10 ** 9 + 7)

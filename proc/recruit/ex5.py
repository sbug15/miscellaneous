import numpy as np


def subsets(arr, k):
    if(k == 0):
        return [[]]
    elif(len(arr) == k):
        return [arr[:]]
    else:
        res = []
        rec = subsets(arr[:-1], k)
        res.extend(rec)
        rec = subsets(arr[:-1], k - 1)
        for lt in rec:
            lt.append(arr[-1])
        res.extend(rec)
        return res

N = int(raw_input())
arr = map(int, raw_input().split(' '))

_sum = 0
for i in range(1, N + 1, 2):
    for subset in subsets(arr, i):
        _sum += np.median(subset)

print int(_sum) % (10 ** 9 + 7)

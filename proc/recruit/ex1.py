import numpy as np

K, L, M = map(int, raw_input().split(' '))
num1 = [1] * K
num2 = [2] * L
arr = num1 + num2


def uniPermutation(nums):
    permutations = [[]]
    for n in nums:
        new_perm = []
        for perm in permutations:
            for i in range(len(perm) + 1):
                new_perm.append(perm[:i] + [n] + perm[i:])
                if i < len(perm) and perm[i] == n:
                    break
            permutations = new_perm
    return permutations


def getNum(listArr):
    a = map(str, listArr)
    return int(''.join(a))

flag = False
for perm in uniPermutation(arr):
    if getNum(perm) % M == 0:
        flag = True
        print getNum(perm)
        break

if flag == False:
    print -1

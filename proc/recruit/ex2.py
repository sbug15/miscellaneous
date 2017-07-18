import numpy as np

length = int(raw_input())
s = raw_input()
numQ = int(raw_input())
larr = []
rarr = []


def countMax(s):
    sArr = ['a', 'c', 'g', 't']
    sFreq = [s.count(l) for l in sArr]
    sFreq = np.array(sFreq)
    indexMax = np.argmax(sFreq)
    return sArr[indexMax]

for i in range(numQ):
    l, r = map(int, raw_input().split(' '))
    print countMax(s[l - 1:r])

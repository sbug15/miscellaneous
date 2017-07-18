from math import ceil

N, M = map(int, raw_input().split(' '))
c = []
for i in range(N):
    c.append(int(raw_input()))

tempPower = sum(c) / M


def timeNeed(c, tempPower):
    _sum = 0
    for i in range(N):
        _sum += ceil(c[i] * 1.0 / tempPower)
    return int(_sum)

needtime = M + 1
while(needtime > M):
    needtime = timeNeed(c, tempPower)
    tempPower += 1

print tempPower - 1

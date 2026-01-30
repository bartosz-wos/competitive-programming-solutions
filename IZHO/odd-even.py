import math
n = int(input())
l = 0
r = 8 * n
while l + 1 < r:
    m = (l + r) // 2
    if m * (m + 1) // 2 < n:
        l = m
    else:
        r = m
print(2 * n - l - 1)

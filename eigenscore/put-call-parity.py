import math

def solve(c: float, s0: float, k: float, r: float, t: float) -> float:
    return c - s0 + k * math.exp(-r * t)


c, s0, k, r, t = map(float, input().split())
print(solve(c, s0, k, r, t))


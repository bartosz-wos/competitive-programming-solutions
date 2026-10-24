import math

def solve(r: float, c: float, t: float) -> float:
    return math.exp(r * t)


r, c, t = map(float, input().split())
print(solve(r, c, t))

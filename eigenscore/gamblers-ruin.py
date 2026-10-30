def solve(p: float, a: int, n: int) -> float:
    if p == 0.5:
        ans = a / n
    else:
        q = 1.0 - p
        r = q / p
        ans = (1 - r**a)/(1 - r**n)
    return ans

parts = input().split()
p, a, n = float(parts[0]), int(parts[1]), int(parts[2])
print(solve(p, a, n))


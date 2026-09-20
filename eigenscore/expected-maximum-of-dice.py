def solve(n: int, m: int) -> float:
    ret: float = float(m)

    for k in range(1, m):
        ret -= (k/m)**n
    
    return round(ret, 7)


n, m = map(int, input().split())
print(solve(n, m))

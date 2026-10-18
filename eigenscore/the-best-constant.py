import sys
import math

def solve(p: int, q: int) -> float:
    a = p / q
    return round(math.pow(math.e / a, a), 10)


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    out = []
    for i in range(t):
        p, q = int(data[1 + 2 * i]), int(data[2 + 2 * i])
        out.append(repr(solve(p, q)))
    print("\n".join(out))


main()

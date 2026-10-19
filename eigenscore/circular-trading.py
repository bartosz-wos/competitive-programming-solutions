import sys
import math


def solve(n: int) -> int:
    return (n // 2) * ((n + 1) // 2)


def main():
    data = sys.stdin.read().split()
    q = int(data[0])
    print("\n".join(str(solve(int(data[1 + t]))) for t in range(q)))


main()


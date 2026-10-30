import sys


def solve(n: int, a: list[list[int]]) -> tuple[int, int, int]:
    row_mins = [min(row) for row in a]
    col_maxs = [max(a[i][j] for i in range(n)) for j in range(n)]

    for i in range(n):
        for j in range(n):
            if a[i][j] == row_mins[i] and a[i][j] == col_maxs[j]:
                return i + 1, j + 1, a[i][j]

    return 1, 1, a[0][0]


def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    a = [[int(x) for x in data[1 + i * n:1 + (i + 1) * n]] for i in range(n)]
    r, c, v = solve(n, a)
    print(r, c, v)


main()

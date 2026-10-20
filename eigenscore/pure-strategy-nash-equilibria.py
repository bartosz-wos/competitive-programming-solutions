import sys


def solve(m: int, n: int, A: list[list[int]], B: list[list[int]]) -> list[tuple[int, int]]:
    col_max = [max(A[i][j] for i in range(m)) for j in range(n)]
    row_max = [max(B[i][j] for j in range(n)) for i in range(m)]
    
    return [
        (i + 1, j + 1)
        for i in range(m)
        for j in range(n)
        if A[i][j] == col_max[j] and B[i][j] == row_max[i]
    ]

def main():
    data = sys.stdin.read().split()
    m, n = int(data[0]), int(data[1])
    vals = [int(t) for t in data[2:]]
    A = [vals[r * n:(r + 1) * n] for r in range(m)]
    B = [vals[m * n + r * n:m * n + (r + 1) * n] for r in range(m)]
    eqs = solve(m, n, A, B)
    print("\n".join([str(len(eqs))] + [f"{i} {j}" for i, j in eqs]))


main()

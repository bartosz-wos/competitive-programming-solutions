import sys

MOD = 998244353

# assume that the dimensions are fine to multiply
def multiply(A, B):
    rows_A = len(A)
    cols_A = len(A[0])
    cols_B = len(B[0])

    C = [[0] * cols_B for _ in range(rows_A)]
    for i in range(rows_A):
        for k in range(cols_A):
            if A[i][k] == 0:
                continue
            for j in range(cols_B):
                C[i][j] = (C[i][j]+A[i][k] * B[k][j]) % MOD
    
    return C

def solve(n: int) -> int:
    ret = [ [1, 0], [0, 1]]
    M = [ [2, 1], [1, 1] ]

    while n > 0:
        if n & 1:
            ret = multiply(ret, M)
        M = multiply(M, M)
        n >>= 1
    
    return ret[0][0]



def main():
    n = int(sys.stdin.read().split()[0])
    print(solve(n))


main()


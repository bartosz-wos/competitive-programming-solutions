import sys
import math
import numpy as np

def solve(x: list[float], h: int) -> list[float]:
    arr = np.array(x, dtype=np.float64)
    n = len(arr)
    p = 8

    samples = n - p - h + 1

    windows = np.column_stack([arr[i : i + samples] for i in range(p)])
    A = np.column_stack([np.ones(samples), windows])

    B = np.column_stack([arr[p + j : p + j + samples] for j in range(h)])

    W, _, _, _ = np.linalg.lstsq(A, B, rcond = None)

    forecasts = np.concatenate(([1.0], arr[-p:])) @ W

    return forecasts.tolist()


def main():
    data = sys.stdin.read().split()
    n, h = int(data[0]), int(data[1])
    x = [float(t) for t in data[2:2 + n]]
    print("\n".join(str(v) for v in solve(x, h)))


main()


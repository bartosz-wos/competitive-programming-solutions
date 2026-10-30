import sys
import math

def solve(values: list[float]) -> tuple[float, int]:
    P: float = 0
    max_drawdown: float = float('-inf')
    max_consecutive_days: int = 0
    current_consecutive_days: int = 0

    for i in range(len(values)):
        P = max(P, values[i])
        current_drawdown = (P - values[i]) / P
        max_drawdown = max(max_drawdown, current_drawdown)

        current_consecutive_days += 1
        if values[i] >= P:
            current_consecutive_days = 0
        
        max_consecutive_days = max(max_consecutive_days, current_consecutive_days)
    
    return [round(max_drawdown, 10), max_consecutive_days]

def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    values = [float(t) for t in data[1:1 + n]]
    mdd, dur = solve(values)
    print(mdd, dur)


main()


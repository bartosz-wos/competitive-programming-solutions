import sys


def solve(positions: list[tuple[int, int]]) -> int:
    positions.sort(key=lambda item: item[0] / item[1])

    total_cost = 0
    curr_time = 0
    for t, c in positions:
        curr_time += t
        total_cost += curr_time * c

    return total_cost
    
def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    positions = [(int(data[1 + 2 * i]), int(data[2 + 2 * i])) for i in range(n)]
    print(solve(positions))


main()


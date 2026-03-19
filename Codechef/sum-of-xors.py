for _ in range(int(input())):
    n, m = map(int, input().split())
    if n == 2 or m == 2:
        print((3*n*m)//2)
    else:
        print(n*m + 4)

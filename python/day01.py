 #!/usr/bin/env python
import sys

def parse(input: str):
    left: list[int] = []
    right: list[int] = []
    for line in input.splitlines():
        s = line.split()
        l, r = tuple(map(int, line.split()))
        left.append(l)
        right.append(r)
    return left, right

def part1(input: str):
    left, right = parse(input)
    left.sort()
    right.sort()
    totalDistance = 0
    for idx, value in enumerate(left):
        dist = abs(value - right[idx])
        totalDistance += dist
    return totalDistance

def part2(input: str):
    left, right = parse(input)
    similarity = 0
    for idx, value in enumerate(left):
        similarity += value * right.count(value)
    return similarity

 
if __name__ == '__main__':
    input = sys.stdin.read()
    print((part1(input), part2(input)))

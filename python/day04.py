 #!/usr/bin/env python
import sys
import re

def _find_in_direction(lines, x, y, search, direction):
    for i in range(0, len(search)):
        y_ = y + (i * direction[1])
        x_ = x + (i * direction[0])
        if y_ < 0 or x_ < 0:
            return False
        try:
            if lines[y_][x_]!= search[i]:
                return False
        except IndexError:
            return False
    return True

def _find(lines, x, y, search):
    numLines = len(lines)
    pos = (x,y)
    findings = 0
    directions = [(1,0),(-1,0),(0,1),(0,-1),(1,1),(-1,1),(1,-1),(-1,-1)]
    for direction in directions:
        if _find_in_direction(lines, x, y, search, direction):
            findings += 1
    return findings


def part1(input: str):
    lines = [line for line in input.splitlines() if len(line) > 0]
    if not all(len(line) == len(lines[0]) for line in lines):
        return -1
    count = 0
    for y in range(0, len(lines)):
        for x in range(0,len(lines[0])):
            count += _find(lines, x, y, "XMAS");
    return count
    lines = [line for line in input.splitlines() if len(line) > 0]
    if not all(len(line) == len(lines[0]) for line in lines):
        return -1
    count = 0
    for y in range(0, len(lines)):
        for x in range(0,len(lines[0])):
            count += _find(lines, x, y, "XMAS");
    return count


def part2(input: str):
    lines = [line for line in input.splitlines() if len(line) > 0]
    if not all(len(line) == len(lines[0]) for line in lines):
        return -1
    count = 0
    for y in range(1, len(lines)-1):
        for x in range(1,len(lines[0])-1):
            if lines[y][x] != 'A':
                continue
            if not (lines[y-1][x-1] in "MS"):
                continue
            if not (lines[y-1][x+1] in "MS"):
                continue
            if not (lines[y+1][x-1] in "MS"):
                continue
            if not (lines[y+1][x+1] in "MS"):
                continue
            if lines[y-1][x-1] == lines[y+1][x+1]:
                continue
            if lines[y-1][x+1] == lines[y+1][x-1]:
                continue
            count += 1
    return count

if __name__ == '__main__':
    input = sys.stdin.read()
    print((part1(input), part2(input)))

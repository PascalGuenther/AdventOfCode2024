 #!/usr/bin/env python
import sys

def _parse(input: str):
    rows = []
    for line in input.splitlines():
        rows.append([int(level) for level in line.split()])
    return rows

def _is_safe(row_of_levels):
    increasing = True
    decreasing = True
    for i, level in enumerate(row_of_levels):
        if i == (len(row_of_levels) - 1):
            return True
        next_ = row_of_levels[i + 1]
        increasing = increasing and (level < next_)
        decreasing = decreasing and (level > next_)
        if (not decreasing) and (not increasing):
            return False
        distance = abs(level - next_)
        if (distance < 1) or (distance > 3):
            return False

def part1(input: str):
    rows = _parse(input)
    return len([row for row in rows if _is_safe(row)])

def part2(input: str):
    def is_safe_allow_single_bad_level(row_of_levels):
        if _is_safe(row_of_levels):
            return True
        for i in range(0, len(row_of_levels)):
            levelsExceptItemI = row_of_levels[:i] + row_of_levels[i+1:]
            if _is_safe(levelsExceptItemI):
                return True
        return False
    rows = _parse(input)
    return len([row for row in rows if is_safe_allow_single_bad_level(row)])

 
if __name__ == '__main__':
    input = sys.stdin.read()
    print((part1(input), part2(input)))

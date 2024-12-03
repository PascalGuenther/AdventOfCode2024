 #!/usr/bin/env python
import sys
import re

def _parse(input: str):
    operations= []
    for left, right, instruction in re.findall(r"(?:mul\((\d+),(\d+)\))|(do\(\)|don't\(\))", input):
        operations.append((int(left), int(right)) if (len(right) > 0) else instruction)
    print(operations)
    return operations

def part1(input: str):
    operations = _parse(input)
    val = sum(x[0] * x[1] for x in operations if not isinstance(x, str))
    return val

def part2(input: str):
    operations = _parse(input)
    active = True
    accumulator = 0
    for operation in operations:
        if isinstance(operation, str):
            active = operation == "do()"
            continue
        if not active:
            continue
        accumulator += operation[0] * operation[1]
    return accumulator

if __name__ == '__main__':
    input = sys.stdin.read()
    print((part1(input), part2(input)))

import day02

input: str = """7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9"""

def test_part1():
    assert(day02.part1(input) == 2)

def test_part2():
    assert(day02.part2(input) == 4)

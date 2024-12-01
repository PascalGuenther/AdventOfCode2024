import day01

input: str = """3   4
4   3
2   5
1   3
3   9
3   3"""

def test_part1():
    assert(day01.part1(input) == 11)

def test_part2():
    assert(day01.part2(input) == 31)

import day04

_input: str = """MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX"""

def test_part1():
    assert(day04.part1(_input) == 18)

def test_part2():
    assert(day04.part2(_input) == 9)

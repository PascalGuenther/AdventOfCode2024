import day03


def test_part1():
    _input: str = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
    assert(day03.part1(_input) == 161)

def test_part2():
    _input: str = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
    assert(day03.part2(_input) == 48)


#include "ipuzzle.hpp"
#include "puzzle_common.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string_view>

namespace AOC::Y2024
{

AOC_Y2024_PUZZLE_CLASS_DECLARATION(03)

namespace
{

TEST(Day03Test, Part1)
{
    auto pPuzzle = std::make_unique<PuzzleDay03>("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))");
    ASSERT_EQ(std::get<std::int64_t>(pPuzzle->Part1()), 161);
}

TEST(Day03Test, Part2)
{
    auto pPuzzle = std::make_unique<PuzzleDay03>("mul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))");
    ASSERT_EQ(std::get<std::int64_t>(pPuzzle->Part2()), 48);
}

} // namespace
} // namespace AOC::Y2024

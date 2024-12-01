
#include "ipuzzle.hpp"
#include "puzzle_common.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string_view>

namespace AOC::Y2024
{

AOC_Y2024_PUZZLE_CLASS_DECLARATION(01)

namespace
{

class Day01Test : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        pPuzzle = std::make_unique<PuzzleDay01>(exampleInput);
    }

    // void TearDown() override {}
    std::unique_ptr<IPuzzle> pPuzzle;
    static constexpr const char * exampleInput = R"DAY01(
3   4
4   3
2   5
1   3
3   9
3   3
)DAY01";
};

TEST_F(Day01Test, Part1)
{
    ASSERT_EQ(std::get<std::int64_t>(pPuzzle->Part1()), 11);
}

TEST_F(Day01Test, Part2)
{
    ASSERT_EQ(std::get<std::int64_t>(pPuzzle->Part2()), 31);
}

} // namespace
} // namespace AOC::Y2024

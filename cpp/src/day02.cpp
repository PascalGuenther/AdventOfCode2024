#include "ipuzzle.hpp"
#include "puzzle_common.hpp"
#include "utils.hpp"

#include <algorithm>
#include <memory>
#include <numeric>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace AOC::Y2024
{

namespace {
    using Row = std::vector<unsigned int>;
    using Parsed = std::vector<Row>;

    AOC_Y2024_CONSTEXPR auto parse_input(std::string_view input_string_view)
    {
        Parsed parsed;
        for(const auto &line : LinesView{input_string_view})
        {
            if(line.empty())
            {
                continue;
            }
            parsed.emplace_back(parse_to_vector_of_numbers<unsigned int, ' '>(line));
        }
        return parsed;
    }

    AOC_Y2024_CONSTEXPR auto is_safe(const Row &row)
    {
        const auto numberOfLevels = row.size();
        bool increasing = true;
        bool decreasing = true;
        for(size_t idx = 0u; idx != (numberOfLevels - 1ul); ++idx)
        {
            const auto level = row[idx];
            const auto nextLevel = row[idx + 1u];
            increasing = increasing && level < nextLevel;
            decreasing = decreasing && level > nextLevel;
            if(!(decreasing || increasing))
            {
                return false;
            }
            const auto distance = (level > nextLevel) ? (level - nextLevel) : (nextLevel - level);
            if((distance < 1u) || (distance > 3))
            {
                return false;
            }
        }
        return true;
    }

    AOC_Y2024_CONSTEXPR auto part_1(const auto &parsedInput)
    {
        return std::ranges::count_if(parsedInput, is_safe);
    }

    AOC_Y2024_CONSTEXPR auto part_2(const auto &parsedInput)
    {   
        const auto is_safe_with_dampener = [](const Row &row) {
            const auto numberOfLevels = row.size();
            if(numberOfLevels < 1u)
            {
                return false;
            }
            if(is_safe(row))
            {
                return true;
            }
            for(size_t drop = 0u; drop != numberOfLevels; ++drop)
            {
                Row rowWithOneElementDropped{row};
                rowWithOneElementDropped.erase(rowWithOneElementDropped.begin() + static_cast<ssize_t>(drop));
                if(is_safe(rowWithOneElementDropped))
                {
                    return true;
                }
            }
            return false;
        };
        return std::ranges::count_if(parsedInput, is_safe_with_dampener);
    }
}

class PuzzleDay02Impl final {
public:
    AOC_Y2024_CONSTEXPR PuzzleDay02Impl(Parsed &&parsed) : parsed(parsed) {}
    Parsed parsed;
};

AOC_Y2024_PUZZLE_CLASS_DECLARATION(02)

PuzzleDay02::PuzzleDay02(const std::string_view input)
    : pImpl(std::make_unique<PuzzleDay02Impl>(parse_input(input)))
{
}

PuzzleDay02::~PuzzleDay02() = default;

[[nodiscard]] IPuzzle::Solution_t PuzzleDay02::Part1()
{
    if (!pImpl || (pImpl->parsed.size() < 1))
    {
        return std::monostate{};
    }
    return part_1(pImpl->parsed);
}

[[nodiscard]] IPuzzle::Solution_t PuzzleDay02::Part2()
{
    if (!pImpl || (pImpl->parsed.size() < 1))
    {
        return std::monostate{};
    }
    return part_2(pImpl->parsed);
}

#if AOC_Y2024_CONSTEXPR_UNIT_TEST
namespace
{
constexpr const char * exampleInput = R"DAY02(
7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9
)DAY02";
consteval bool TestDay02()
{
    Parsed parsed{parse_input(exampleInput)};

    if (2 != part_1(parsed))
    {
        return false;
    }

    return 4 == part_2(parsed);
}

static_assert(TestDay02(), "");
} // namespace
#endif // AOC_Y2024_CONSTEXPR_UNIT_TEST

} // namespace AOC::Y2024

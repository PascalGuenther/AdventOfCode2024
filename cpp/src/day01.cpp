#include "ipuzzle.hpp"
#include "puzzle_common.hpp"
#include "utils.hpp"
#include "ctre.hpp"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string_view>
#include <utility>
#include <vector>

namespace AOC::Y2024
{

namespace {
    struct Parsed {
        std::vector<int> left;
        std::vector<int> right;
    };

    AOC_Y2024_CONSTEXPR auto parse_input(std::string_view input_string_view)
    {
        LinesView lines{input_string_view};
        Parsed parsed{};
        for(const auto &line: lines) {
            if(line.empty())
            {
                continue;
            }
            if (auto [m, l, r] = ctre::match<"^\\s*(\\d+)\\s+(\\d+)\\s*$">(line); m)
            {
                parsed.left.emplace_back(parse_number<int>(l));
                parsed.right.emplace_back(parse_number<int>(r));
            }
            else
            {
                return Parsed{};
            }
        }
        return parsed;
    }


    AOC_Y2024_CONSTEXPR auto part_1(const auto &parsedInput)
    {
        std::vector<int> leftSorted(parsedInput.left.size());
        std::partial_sort_copy(std::begin(parsedInput.left), std::end(parsedInput.left), std::begin(leftSorted), std::end(leftSorted));
        std::vector<int> rightSorted(parsedInput.right.size());
        std::partial_sort_copy(std::begin(parsedInput.right), std::end(parsedInput.right), std::begin(rightSorted), std::end(rightSorted));
        int totalDistance{0};
        const auto numberOfElements = leftSorted.size();
        for(size_t idx = 0u; idx != numberOfElements; ++idx)
        {
            const auto distance = leftSorted[idx] - rightSorted[idx];
            const auto distanceAbs = distance < 0 ? (-1 * distance) : distance;
            totalDistance += distanceAbs;
        }
        return totalDistance;
    }

    AOC_Y2024_CONSTEXPR auto part_2(const auto &parsedInput)
    {
        int similarity{0};
        for(const auto &l : parsedInput.left)
        {
            similarity += l * std::count(parsedInput.right.begin(), parsedInput.right.end(), l);
        }
        return similarity;
    }
}

class PuzzleDay01Impl final {
public:
    AOC_Y2024_CONSTEXPR PuzzleDay01Impl(Parsed &&parsed) : parsed(parsed) {}
    Parsed parsed;
};

AOC_Y2024_PUZZLE_CLASS_DECLARATION(01)

PuzzleDay01::PuzzleDay01(const std::string_view input)
    : pImpl(std::make_unique<PuzzleDay01Impl>(parse_input(input)))
{
}

PuzzleDay01::~PuzzleDay01() = default;

[[nodiscard]] IPuzzle::Solution_t PuzzleDay01::Part1()
{
    if (!pImpl || (pImpl->parsed.left.size() < 1))
    {
        return std::monostate{};
    }
    return part_1(pImpl->parsed);
}

[[nodiscard]] IPuzzle::Solution_t PuzzleDay01::Part2()
{
    if (!pImpl || (pImpl->parsed.left.size() < 1))
    {
        return std::monostate{};
    }
    return part_2(pImpl->parsed);
}

#if AOC_Y2024_CONSTEXPR_UNIT_TEST
namespace
{
constexpr const char * exampleInput = R"DAY01(
3   4
4   3
2   5
1   3
3   9
3   3
)DAY01";
consteval bool TestDay01()
{
    Parsed parsed{parse_input(exampleInput)};

    if (11 != part_1(parsed))
    {
        return false;
    }

    return 31 == part_2(parsed);
}

static_assert(TestDay01(), "");
} // namespace
#endif // AOC_Y2024_CONSTEXPR_UNIT_TEST

} // namespace AOC::Y2024

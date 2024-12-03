#include "ipuzzle.hpp"
#include "puzzle_common.hpp"
#include "utils.hpp"
#include "ctre.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace AOC::Y2024
{

namespace {
    using Operand = uint32_t;
    enum Instruction {mul, do_, dont,};
    struct Operation {
        Instruction instruction;
        std::pair<Operand, Operand> operands{};
    };
    using Parsed = std::vector<Operation>;

    AOC_Y2024_CONSTEXPR auto parse_input(std::string_view input_string_view)
    {
        Parsed parsed;
        const auto matches = ctre::multiline_search_all<R"((?:mul\((\d+),(\d+)\))|(do\(\)|don't\(\)))">(input_string_view);
        for (const auto& match : matches)
        {
            if (match.get<0>() == "do()")
            {
                parsed.emplace_back(Operation{.instruction = Instruction::do_});
            }
            else if (match.get<0>() == "don't()")
            {
                parsed.emplace_back(Operation{.instruction = Instruction::dont});
            }
            else
            {
                parsed.emplace_back(Operation{.instruction = Instruction::mul, .operands{ parse_number<Operand>(match.get<1>()), parse_number<Operand>(match.get<2>())}});
            }
        }
        return parsed;
    }

    AOC_Y2024_CONSTEXPR auto part_1(const Parsed &parsed)
    {
        return std::accumulate(
            parsed.begin(), parsed.end(), 0u, [](const auto &acc, const auto &operation){
                return (operation.instruction == Instruction::mul)
                  ? (acc + (operation.operands.first * operation.operands.second))
                  : acc;
            });   
    }

    AOC_Y2024_CONSTEXPR auto part_2(const auto &parsed)
    {
        return std::accumulate(
            parsed.begin(), parsed.end(), 0u, [enabled = true] (const auto &acc, const auto &operation) mutable {
                switch(operation.instruction) {
                    using enum Instruction;
                    case do_:
                        enabled = true;
                        return acc;
                    case dont:
                        enabled = false;
                        return acc;
                    default:
                        return acc + (enabled ? (operation.operands.first * operation.operands.second): 0u);
                }
            });
    }
}

class PuzzleDay03Impl final {
public:
    AOC_Y2024_CONSTEXPR PuzzleDay03Impl(Parsed &&parsed) : parsed(parsed) {}
    Parsed parsed;
};

AOC_Y2024_PUZZLE_CLASS_DECLARATION(03)

PuzzleDay03::PuzzleDay03(const std::string_view input)
    : pImpl(std::make_unique<PuzzleDay03Impl>(parse_input(input)))
{
}

PuzzleDay03::~PuzzleDay03() = default;

[[nodiscard]] IPuzzle::Solution_t PuzzleDay03::Part1()
{
    if (!pImpl || (pImpl->parsed.size() < 1))
    {
        return std::monostate{};
    }
    return part_1(pImpl->parsed);
}

[[nodiscard]] IPuzzle::Solution_t PuzzleDay03::Part2()
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

consteval bool TestDay03()
{
    Parsed parsed1{parse_input("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))")};
    Parsed parsed2{parse_input("mul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))")};

    if (161 != part_1(parsed1))
    {
        return false;
    }

    return 48 == part_2(parsed2);
}

static_assert(TestDay03(), "");
} // namespace
#endif // AOC_Y2024_CONSTEXPR_UNIT_TEST

} // namespace AOC::Y2024

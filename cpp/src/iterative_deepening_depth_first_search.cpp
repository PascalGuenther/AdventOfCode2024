#include "puzzle_common.hpp"
#include "ipuzzle.hpp"
#include "utils.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
//#include <functional>
//#include <iterator>
#include <limits>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <iostream>
namespace AOC::Y2024
{

namespace
{

    using Coordinate = std::int32_t;
    using Distance = Coordinate;
    using Position = std::pair<Coordinate, Coordinate>;
    using Row = std::vector<char>;
    using Map = std::vector<Row>;
    using Path = std::vector<Position>;

    static constexpr Position invalidPosition {-1, -1};

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto parse_map(std::string_view input) -> Map
    {
        Map map;
        map.reserve(32);
        bool foundS = false;
        bool foundE = false;
        for (const auto &line : LinesView{input})
        {
            if ((line.empty()) || ((map.size() > 1u) && (map[0].size() != line.size())))
            {
                return Map{};
            }
            auto &row = map.emplace_back();
            if (map.size() > 1u)
            {
                row.reserve(map[0].size());
            }
            for (const char &c :line)
            {
                if (c == 'S')
                {
                    if (foundS)
                    {
                        return Map{};
                    }
                    foundS = true;
                }
                else if (c == 'E')
                {
                    if (foundE)
                    {
                        return Map{};
                    }
                    foundE = true;
                }
                else if ((c < 'a') || (c > 'z'))
                {
                    return Map{};
                }
                row.push_back(c);
            }
        }
        if (!foundS || !foundE || (map.size() > std::numeric_limits<Coordinate>::max()) || (map[0].size() > std::numeric_limits<Coordinate>::max()))
        {
            return Map{};
        }
        return map;
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto add(const auto &lhs, const auto &rhs)
    {
        return Position{lhs.first + rhs.first, lhs.second + rhs.second};
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto subtract(const auto &lhs, const auto &rhs)
    {
        return Position{lhs.first - rhs.first, lhs.second - rhs.second};
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto manhattan_distance(const auto &lhs, const auto &rhs)
    {
        const auto dist2d = subtract(rhs, lhs);
        return Distance{ AOC::Y2024::abs(dist2d.first) + AOC::Y2024::abs(dist2d.second) };
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto is_within_map(const Position &position, const Map &map)
    {
        if ((position.first < 0) || position.second < 0)
        {
            return false;
        }
        return (static_cast<std::size_t>(position.first) < map.front().size()) && (static_cast<std::size_t>(position.second) < map.size());
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto not_yet_visited(const Path &path)
    {
        const auto &desiredPos = path.back();
        return (path.end() - 1u) == std::find(path.begin(), path.end() - 1u, desiredPos);
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto is_reachable(const Path &path, const Map &map)
    {
        const auto &newPosition = path.back();
        if (!is_within_map(newPosition, map))
        {
            return false;
        }
        const auto &oldPosition = path[path.size() - 2u];
        const auto oldValue = map[static_cast<std::size_t>(oldPosition.second)][static_cast<std::size_t>(oldPosition.first)];
        const auto newValue = map[static_cast<std::size_t>(newPosition.second)][static_cast<std::size_t>(newPosition.first)];
        const auto adjustedOldValue = (oldValue == 'S') ? 'a' : oldValue;
        const auto adjustedNewValue = (newValue == 'E') ? 'z' : newValue;
        const bool isTooHigh = adjustedNewValue > (adjustedOldValue + 1);
        if (isTooHigh)
        {
            return false;
        }
        return not_yet_visited(path);
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto find(const Map &map, char searchFor)
    {
        for (std::size_t row = 0u; row != map.size(); ++row)
        {
            for (std::size_t col = 0u; col != map[0].size(); ++col)
            {
                if (map[row][col] == searchFor)
                {
                    return Position{ static_cast<Coordinate>(col), static_cast<Coordinate>(row) };
                }
            }
        }
        return invalidPosition;
    }



    AOC_Y2024_CONSTEXPR auto depth_first_search(const Map &map, const Position &target, Path &path, Distance &shortest, Distance depthLimit)
    {
        const auto pathLen = path.size() - 1u;
        if (pathLen >= static_cast<std::size_t>(std::min(depthLimit, shortest)))
        {
            return;
        }
        const auto distance2d = subtract(target, path.back());
        std::size_t preferredDirection;
        bool startHorizontally = AOC::Y2024::abs(distance2d.second) > AOC::Y2024::abs(distance2d.first);
        if (startHorizontally)
        {
            preferredDirection = (distance2d.second > 0) ? 0u : 1u;
        }
        else
        {
            preferredDirection = (distance2d.first > 0) ? 2 : 3;
        }
        static constexpr std::array<Position, 4u> directions
        {
            Position{ 0,  1},
            Position{ 0, -1},
            Position{ 1,  0},
            Position{-1,  0},
        };
        for (std::size_t directionIndex = 0u; directionIndex != directions.size(); ++directionIndex)
        {
            const std::size_t adjustedDirectionIndex = (directionIndex + preferredDirection) % directions.size();
            const auto &direction = directions[adjustedDirectionIndex];
            path.push_back(add(path.back(), direction));
            if (is_reachable(path, map))
            {
                if (path.back() == target)
                {
                    shortest = static_cast<Distance>(pathLen + 1u);
                    for (const auto &p : path)
                    {
                        std::cout << p.second << ' ' << p.first << " | ";
                    }
                    std::cout << "\n\n";
                }
                else
                {
                    depth_first_search(map, target, path, shortest, depthLimit);
                }
            }
            else {
                std::cout << "Len: " << pathLen << ' ' << path[path.size() - 2u].second << ',' << path[path.size() - 2u].first
                          << "     " << path.back().second << ',' << path.back().first << '\n';
            }
            path.pop_back();
        }
    }

    AOC_Y2024_CONSTEXPR auto iterative_deepening_depth_first_search(const Map &map, const Position &target, Path &path, Distance minDepth)
    {
        Distance shortest = std::numeric_limits<Distance>::max();
        for (Distance depthLimit = minDepth; depthLimit < shortest; ++depthLimit)
        {
            std::cout << "Depth limit " << depthLimit << '\n';
            depth_first_search(map, target, path, shortest, depthLimit);
        }
        return shortest;
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto find_shortest_path(const Map &map) -> IPuzzle::Solution_t
    {
        const auto startPosition = find(map, 'S');
        const auto endPosition = find(map, 'E');
        if ((startPosition == invalidPosition) || (endPosition == invalidPosition))
        {
            return std::monostate{};
        }
        Path path;
        const Distance manhattanDistance = manhattan_distance(startPosition, endPosition);
        if (manhattanDistance < 1)
        {
            return std::monostate{};
        }
        path.reserve(static_cast<std::size_t>(manhattanDistance + 1));
        path.push_back(startPosition);
        return iterative_deepening_depth_first_search(map, endPosition, path, 2* manhattanDistance);
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto part_1(const auto &map) -> IPuzzle::Solution_t
    {
        if (map.size() < 1u)
        {
            return std::monostate{};
        }
        return find_shortest_path(map);
    }

    [[nodiscard]] AOC_Y2024_CONSTEXPR auto part_2(const auto &map) -> IPuzzle::Solution_t
    {
        return part_1(map);
    }


} // namespace


class PuzzleDay12Impl final {
  public:
    AOC_Y2024_CONSTEXPR PuzzleDay12Impl(std::string_view input) : map(parse_map(input)) {}
    Map map;
};

AOC_Y2024_PUZZLE_CLASS_DECLARATION(12)

PuzzleDay12::PuzzleDay12(const std::string_view input)
    : pImpl(std::make_unique<PuzzleDay12Impl>(input))
{
}
PuzzleDay12::~PuzzleDay12() = default;

[[nodiscard]] IPuzzle::Solution_t PuzzleDay12::Part1()
{
    return part_1(pImpl->map);
}

[[nodiscard]] IPuzzle::Solution_t PuzzleDay12::Part2()
{
    return part_2(pImpl->map);
}

#if 0 // AOC_Y2024_CONSTEXPR_UNIT_TEST
namespace
{

static constexpr const char *exampleInput1 =
R"ExampleInput1(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi
)ExampleInput1";

consteval bool TestDay12()
{
    PuzzleDay12Impl parsed1{exampleInput1};
    if (10605 != std::get<std::int64_t>(part_1(parsed1.monkeys)))
    {
        return false;
    }

    // This takes way too long
    // if (2713310158 != std::get<std::int64_t>(part_2(parsed1.monkeys)))
    // {
    //     return false;
    // }

    return true;
}
static_assert(TestDay12(), "Wrong results for example input");

} // namespace
#endif // AOC_Y2024_CONSTEXPR_UNIT_TEST

} // namespace AOC::Y2024

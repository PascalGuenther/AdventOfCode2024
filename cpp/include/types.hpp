#if !defined(AOC_Y2024_TYPES_HPP)
#define AOC_Y2024_TYPES_HPP (1)

#if !defined(AOC_Y2024_API)
#define AOC_Y2024_API
#endif

#if ((defined(__GNUC__) && (__GNUC__ >= 12)) || (defined(__clang__) && (__cplusplus >= 199711L)))
#define AOC_Y2024_CONSTEXPR_UNIT_TEST   (1)
#else
#define AOC_Y2024_CONSTEXPR_UNIT_TEST   (0)
#endif


#if AOC_Y2024_CONSTEXPR_UNIT_TEST
#define AOC_Y2024_CONSTEXPR constexpr
#else
#define AOC_Y2024_CONSTEXPR
#endif

#endif // !defined(AOC_Y2024_TYPES_HPP)

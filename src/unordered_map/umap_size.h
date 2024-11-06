#ifndef UMAP_SIZE_H
#define UMAP_SIZE_H

#include <array>
#include <limits>

namespace s21::um {
struct map_size {
    static constexpr const double kResizeAlpha{0.75};
    
    static constexpr const std::array<std::size_t, 31> size{
        0ull,          4ull,
        12ull,         28ull,
        60ull,         124ull,
        252ull,        508ull,
        1020ull,       2044ull,
        4092ull,       8188ull,
        16380ull,      32764ull,
        65532ull,      131068ull,
        262140ull,     524284ull,
        1048572ull,    2097148ull,
        4194300ull,    8388604ull,
        16777212ull,   33554428ull,
        67108860ull,   134217724ull,
        268435452ull,  536870908ull,
        1073741820ull, 2147483640ull,
        std::numeric_limits<std::size_t>::max()
    };
};
} // namespace s21::um

#endif // UMAP_SIZE_H

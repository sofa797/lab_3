#pragma once
#include <vector>

// Caclculate average value for each key.
template<typename Key_t, typename Value_t>
std::vector<std::pair<Key_t, Value_t>> AvgWithPartitioning(const std::vector<std::pair<Key_t, Value_t>>& kv_array
    , std::size_t block_size = 8)
{
    return std::vector<std::pair<Key_t, Value_t>>();
}

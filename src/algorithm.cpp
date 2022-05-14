#include <opencv2/opencv.hpp>

#include <iostream>
#include <algorithm>

#include "algorithm.hpp"

std::vector<std::array<uchar, 3>> remove_duplicates(std::vector<std::array<uchar, 3>> &vec)
{
    // runs in O(n log n) time but only needs to run once. Maybe refactor?
    std::sort(vec.begin(), vec.end());

    auto it = std::unique(vec.begin(), vec.end());
    vec.resize(std::distance(vec.begin(), it));

    return vec;
}
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

// long distance_function(int &x, int &y, cv::Mat &img_to_check, cv::Vec3b &a)
// {
//     cv::Vec3b b = img_to_check.at<cv::Vec3b>(y, x);
//     return std::pow(a.val[0] - b.val[0], 2) + std::pow(a.val[1] - b.val[1], 2) + std::pow(a.val[2] - b.val[2], 2);
// }

// std::array<long, 3> bresenham_line(cv::Point2i &p1, cv::Point2i &p2, cv::Mat &im, cv::Mat &newim, cv::Vec3b &r_color)
// {
//     int x1 = p1.x;
//     int y1 = p1.y;
//     int x2 = p2.x;
//     int y2 = p2.y;
//     std::array<long, 3> rmse_sum;

//     const bool steep = (std::abs(y2 - y1) > std::abs(x2 - x1));

//     if (steep)
//     {
//         std::swap(x1, y1);
//         std::swap(x2, y2);
//     }
//     if (x1 > x2)
//     {
//         std::swap(x1, x2);
//         std::swap(y1, y2);
//     }

//     const int dx = x2 - x1;
//     const int dy = std::abs(y2 - y1);

//     float error = dx / 2.0f;
//     const int ystep = (y1 < y2) ? 1 : -1;
//     int y = y1;

//     for (int x = x1; x < x2; ++x)
//     {
//         ++rmse_sum[0];
//         if (steep)
//         {
//             rmse_sum[1] += distance_function(y, x, newim, r_color);
//             rmse_sum[2] += distance_function(y, x, im, r_color);
//         }
//         else
//         {
//             rmse_sum[1] += distance_function(y, x, newim, r_color);
//             rmse_sum[2] += distance_function(y, x, im, r_color);
//         }
//     }
//     error -= dy;
//     if (error < 0)
//     {
//         y+= ystep;
//         error += dx;
//     }

//     RMSE(rmse_sum);
//     return;
// }

// int RMSE(std::array<long, 3> &rmse_sum)
// {
//     long n = rmse_sum[0];
//     long sum_newimg_residual = 

// }
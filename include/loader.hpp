#pragma once

#include <opencv2/imgcodecs.hpp>

#include <string>

cv::Mat load_image(std::string filepath);
cv::Mat new_image(int height, int width);
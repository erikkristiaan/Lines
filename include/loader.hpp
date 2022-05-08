#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

cv::Mat load_image(std::string filepath);
cv::Mat new_image(int height, int width);
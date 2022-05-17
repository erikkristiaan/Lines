#include "loader.hpp"

#include <opencv2/imgcodecs.hpp>

#include <string>

cv::Mat load_image(std::string filepath)
{
    filepath = cv::samples::findFile(filepath);
    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);

    return image;
}

cv::Mat new_image(int height, int width)
{
    cv::Mat newimg(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    return newimg;
}
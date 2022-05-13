#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

int main()
{
    std::string filepath = cv::samples::findFile("default.jpg");
    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);

    return 0;
}
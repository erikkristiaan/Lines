#pragma once

#include <opencv2/imgcodecs.hpp>

#include <string>

struct Arguments
{
    // Creates a struct of arguments to pass.
    int primitive_size;
    int iters;
    int frames;
    int palette;
    bool show_image;
    bool anti_aliasing;
    std::string filename;
};

// main function to run the iterator
void iterate(cv::Mat &img, Arguments args);
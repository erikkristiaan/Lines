#include "iterator.hpp"

#include "algorithm.hpp"
#include "loader.hpp"
#include "output.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <cmath>
#include <iostream>
#include <time.h>
#include <vector>

cv::Point2i get_first_point(int &height, int &width)
{
    // return random (x,y) point from the canvas
    return cv::Point2i(rand() % width + 1, rand() % height + 1);
}

cv::Point2i get_second_point(int &height, int &width, int &line_length, cv::Point2i &point1)
{
    using std::pow;
    using std::sqrt;

    int x1 = point1.x;
    int y1 = point1.y;
    bool is_pos = rand() % 2;
    bool v_dist = rand() % 2;
    int x2;
    int y2;

    if (v_dist)
    {
        int x1_min = x1 - line_length;
        int x1_max = x1 + line_length;

        x2 = rand() % (x1_max - x1_min + 1) + x1_min;

        if (is_pos)
            y2 = sqrt( pow(line_length,2) - pow(x2 - x1,2) ) + y1;
        else
            y2 = -sqrt( pow(line_length,2) - pow(x2 - x1,2) ) + y1;         
    }
    else
    {
        int y1_min = y1 - line_length;
        int y1_max = y1 + line_length;

        y2 = rand() % (y1_max - y1_min + 1) + y1_min;

        if (is_pos)
            x2 = sqrt( pow(line_length,2) - pow(y2 - y1,2) ) + x1;
        else
            x2 = -sqrt( pow(line_length,2) - pow(y2 - y1,2) ) + x1;        
    }

    // If x2 / y2 values are outside of canvas bounds, set x2 / y2 to min or max of canvas bounds
    if (x2 < 0) {x2 = 0;}
    if (x2 > width) {x2 = width - 1;}

    if (y2 < 0) {y2 = 0;}
    if (y2 > height) {y2 = height - 1;}

    return cv::Point2i(x2, y2);
}

std::vector<std::array<uchar, 3>> get_palette(int &height, int &width, cv::Mat &img, bool make_unique)
{
    std::vector<std::array<uchar, 3>> palette;

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            uchar B = img.at<cv::Vec3b>(y,x)[0];
            uchar G = img.at<cv::Vec3b>(y,x)[1];
            uchar R = img.at<cv::Vec3b>(y,x)[2];

            palette.push_back({B, G, R});
        }
    }

    if (make_unique)
        palette = remove_duplicates(palette);

    return palette;
}

std::array<uchar, 3> random_sample(std::vector<std::array<uchar, 3>> &vec)
{
    uint32_t index = rand() % vec.size();
    auto sample = vec[index];

    return sample;
}

cv::Vec3b get_color(int &height, int &width, int option, std::vector<std::array<uchar, 3>> &p)
{
    if (option == 1) 
    {
        // return BGR value from random value from 0 - 255 for each channel
        cv::Vec3b color(rand() % 256, rand() % 256, rand() % 256);
        return color;
    }
    else if (option == 2 || option == 3) 
    {
        // return random BGR value from input palette vector
        auto sample = random_sample(p);
        cv::Vec3b color(sample[0], sample[1], sample[2]); // BGR
        return color;  
    }
    else 
    {
        throw std::invalid_argument("Did not recieve valid color palette input.");
    }
}

uint32_t get_residual(cv::Vec3b &a, cv::Vec3b &b)
{
    return std::pow(a.val[0] - b.val[0], 2) + std::pow(a.val[1] - b.val[1], 2) + std::pow(a.val[2] - b.val[2], 2);
}

uint32_t get_RMSE(int &n, uint32_t &rsum)
{
    if (n != 0)
        return std::sqrt(rsum / n);

    return 0;
}

bool should_plot_line(cv::Point2i &p1, cv::Point2i &p2, cv::Mat &img, cv::Mat &newimg, cv::Vec3b &rand_color)
{
    uint32_t rsum_new = 0;
    uint32_t rsum_old = 0;
    int n = 0;

    cv::LineIterator line_iter(img, p1, p2, 8);
    cv::Vec3b buffer(line_iter.count); // buffer for BGR values

    for (int i = 0; i < line_iter.count; i++, ++line_iter)
    {
        n++;
        // Get BGR Vec3b at pos (x,y)
        auto im_color = img.at<cv::Vec3b>(line_iter.pos());
        auto new_color = newimg.at<cv::Vec3b>(line_iter.pos());

        rsum_new += get_residual(im_color, rand_color);
        rsum_old += get_residual(im_color, new_color);
    }
    auto new_RMSE = get_RMSE(n, rsum_new);
    auto old_RMSE = get_RMSE(n, rsum_old);

    if (new_RMSE < old_RMSE)
        return true;
    else
        return false;
}

void iterate(cv::Mat &img, Arguments args)
{
    // seed current time for rand() function
    srand (time(NULL));

    // set up
    std::vector<std::array<uchar, 3>> color_palette;
    int height = img.size().height;
    int width = img.size().width;
    int aliasing_option = (args.anti_aliasing == true ? 16 : 8); // if anti-aliasing is on set to 16, else set to 8.

    if (args.palette == 2)
        color_palette = get_palette(height, width, img, false); // return full palette
    if (args.palette == 3)
        color_palette = get_palette(height, width, img, true); // return unique palette

    for (int f = 0; f < args.frames; ++f) 
    {
        cv::Mat newimg = new_image(height, width); // Create blank image

        for (int i = 1; i <= args.iters; ++i) 
        {
            // Get two points and a random color
            auto rand_color = get_color(height, width, args.palette, color_palette);
            auto point1 = get_first_point(height, width);
            auto point2 = get_second_point(height, width, args.primitive_size, point1);

            if (should_plot_line(point1, point2, img, newimg, rand_color))
                line(newimg, point1, point2, rand_color, 1, aliasing_option);

            // output progress to console
            if (i % (args.iters / 20) == 0)
                output_to_console(i, args.iters);
        }
        finished_frame(f, args.frames, newimg);
    }
}
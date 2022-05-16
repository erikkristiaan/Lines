#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "loader.hpp"
#include "output.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

cv::Point2i get_first_point(int &height, int &width)
{
    // return random (x,y) point from the canvas
    return cv::Point2i(rand() % width + 1, rand() % height + 1);
}

cv::Point2i get_second_point(int &height, int &width, int &line_length, cv::Point2i &point1)
{
    // return (x,y) point from first (x,y) point +/- line_length within canvas bounds
    int x_min = point1.x - line_length;
    int x_max = point1.x + line_length;

    int y_min = point1.y - line_length;
    int y_max = point1.y + line_length;

    int i = rand() % (x_max - x_min + 1) + x_min;
    int j = rand() % (y_max - y_min + 1) + y_min; // create point from px +/- line

    if (i < 0) {i = 0;}
    if (i > width) {i = width;}

    if (j < 0) {j = 0;}
    if (j > height) {j = height;}

    return cv::Point2i(i, j);
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
    {
        palette = remove_duplicates(palette);
    }
    return palette;
}

std::array<uchar, 3> random_sample(std::vector<std::array<uchar, 3>> &vec)
{
    uint32_t index = rand() % vec.size();
    auto sample = vec[index];

    return sample;
}

cv::Vec3b get_color(int &height, int &width, cv::Mat &img, int option, std::vector<std::array<uchar, 3>> &p)
{
    if (option == 1) 
    {
        // return BGR value from random value from 0 - 255 for each channel
        cv::Vec3b color(rand() % 256, rand() % 256, rand() % 256);
        return color;
    }
    else if (option == 2 || option == 3) 
    {
        // return random BGR value from input vector
        auto sample = random_sample(p);
        cv::Vec3b color(sample[0], sample[1], sample[2]);
        return color;  
    }
    else 
    {
        throw std::invalid_argument("Did not recieve valid color palette input.");
    }
}

long get_residual(cv::Vec3b &a, cv::Vec3b &b)
{
    return std::pow(a.val[0] - b.val[0], 2) + std::pow(a.val[1] - b.val[1], 2) + std::pow(a.val[2] - b.val[2], 2);
}

long double get_RMSE(int n, long rsum)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return std::sqrt(rsum / n);
    }
}

bool should_plot_line(cv::Point2i &p1, cv::Point2i &p2, cv::Mat &img, cv::Mat &newimg, cv::Vec3b &rand_color)
{
    unsigned long long int rsum_new = 0;
    unsigned long long int rsum_old = 0;

    cv::LineIterator line_iter(img, p1, p2, 8);
    cv::Vec3b buffer(line_iter.count); // buffer for BGR values
    int n = 0;

    for (int i = 0; i < line_iter.count; i++, ++line_iter)
    {
        ++n;
        // Get BGR Vec3b at pos (x,y)
        cv::Vec3b im_color = img.at<cv::Vec3b>(line_iter.pos());
        cv::Vec3b new_color = newimg.at<cv::Vec3b>(line_iter.pos());

        rsum_new += get_residual(im_color, rand_color);
        rsum_old += get_residual(im_color, new_color);
    }
    long double new_RMSE = get_RMSE(n, rsum_new);
    long double old_RMSE = get_RMSE(n, rsum_old);

    if (new_RMSE < old_RMSE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void iterate(cv::Mat &img, int prim_size, int iters, int frames, int p_option, bool anti_a)
{
    srand (time(NULL)); // Intialize seed for rand() function

    int height = img.size().height;
    int width = img.size().width;
    std::vector<std::array<uchar, 3>> color_palette;

    int a_a = (anti_a == true ? 16 : 8); // return 16 if aa == true else return 8 for line options
    // std::cout << "anti-aliasing: " << a_a << std::endl; // debug

    if (p_option == 2) 
    {
        // return full color palette
        color_palette = get_palette(height, width, img, false);
    }
    if (p_option == 3) 
    {
        // return unique color palette
        color_palette = get_palette(height, width, img, true);
    }

    for (int f = 0; f < frames; ++f) 
    {
        
        cv::Mat newimg = new_image(height, width); // Create blank image

        for (int i = 1; i <= iters; ++i) 
        {
            // Get two points and a random color
            auto rand_color = get_color(height, width, img, p_option, color_palette);
            auto point1 = get_first_point(height, width);
            auto point2 = get_second_point(height, width, prim_size, point1);

            if (should_plot_line(point1, point2, img, newimg, rand_color))
            {
                line(newimg, point1, point2, rand_color, 1, a_a);
            }
            // output progress to console
            if (i % (iters / 20) == 0)
            {
                output_to_console(i, iters);
            }
        }
        finished_frame(f, frames, newimg);
    }
}
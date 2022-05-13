#include <iostream>
#include <time.h>
#include <cmath>

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

cv::Vec3b get_color(int &height, int &width, cv::Mat &img, int option) 
{
    // return Vec3b BGR value from either canvas palette or random val
    if (option == 1) {
        cv::Vec3b color(rand() % 256, rand() % 256, rand() % 256);
        return color;
    }
    else if (option == 2) {
        cv::Vec3b color = img.at<cv::Vec3b>(rand() % height + 1, rand() % width + 1);
        return color;
    }
    else {
        throw std::invalid_argument("Did not recieve valid color palette input.");
    }
}

long euclidean_dist(cv::Vec3b &a, cv::Vec3b &b)
{
    // return the euclidean distance between BGR values at (x1, y1) and (x2, y2)
    using std::pow;
    using std::sqrt;
    return sqrt(pow(a.val[0] - b.val[0], 2) + pow(a.val[1] - b.val[1], 2) + pow(a.val[2] - b.val[2], 2));
}

void iterate(cv::Mat &img, int prim_size, int iters, int frames, int cpalette, bool anti_a)
{
    srand (time(NULL)); // Intialize seed for rand() function

    int height = img.size().height;
    int width = img.size().width;

    int a_a = (anti_a == true ? 16 : 8); // return 16 if aa == true else return 8 for line options
    // std::cout << "anti-aliasing: " << a_a << std::endl; // debug

    for (int f = 0; f < frames; f++) {
        
        cv::Mat newimg = new_image(height, width); // Create blank image

        for (int i = 1; i <= iters; i++) {
            long old_dist = 0;
            long new_dist = 0;

            // Get two points and a random color
            auto rand_color = get_color(height, width, img, cpalette);
            auto point1 = get_first_point(height, width);
            auto point2 = get_second_point(height, width, prim_size, point1);

            cv::LineIterator line_iter(img, point1, point2, 8);
            cv::Vec3b buffer(line_iter.count); // buffer for BGR values

            for (int i = 0; i < line_iter.count; i++, ++line_iter) {

                // Get BGR Vec3b at pos (x,y)
                cv::Vec3b im_color = img.at<cv::Vec3b>(line_iter.pos());
                cv::Vec3b new_color = newimg.at<cv::Vec3b>(line_iter.pos()); 

                new_dist += euclidean_dist(im_color, rand_color);
                old_dist += euclidean_dist(im_color, new_color);   
            }
            // if new score is less than old score, add line to canvas
            if (new_dist < old_dist) {
                line(newimg, point1, point2, rand_color, 1, a_a);
            }
            // output progress to console
            if (i % (iters / 20) == 0) {
                output_to_console(i, iters);
            }
        }
        finished_frame(f, frames, newimg);
    }
}
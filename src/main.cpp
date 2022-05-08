#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <CLI11.hpp>

#include "iterator.hpp"
#include "loader.hpp"

int main (int argc, char **argv) 
{
    int prim_size = 30;
    int iters = 20000000;
    int frames = 1;
    bool show_image_flag = false;
    std::string filename = "../examples/default.jpg";
    int cpalette = 1;
    bool anti_a = true;
    std::string dist_func = "euclidean";

    CLI::App app("Polygons");
        app.add_option("--primitives,-p", prim_size, "Primitive size in pixels. (default: 30)");
        app.add_option("--iters,-i", iters, "Number of iterations to complete (default 10000000)");
        app.add_option("--frames,-x", frames, "Number of frames to render (default: 1)");
        app.add_option("--show,-s", show_image_flag, "Show result when iterations have completed. (default: false)");
        app.add_option("--filename,-f", filename, "Filename.");
        app.add_option("--pallet,-c", cpalette, "The color pallet to use. (default: 1");
        app.add_option("--antialiasing,-a", anti_a, "Use anti-aliasing (default: true)");
        //app.add_option("--distance,-d", dist_func, "The distance function to use (default: euclidean)")

    CLI11_PARSE(app, argc, argv);

    // int x = 100;
    // iterate(x);

    std::string f = cv::samples::findFile(filename);
    cv::Mat img = cv::imread(f, cv::IMREAD_COLOR);

    std::cout << "Iterating over: " << filename << std::endl;

    iterate(img, prim_size, iters, frames, cpalette, anti_a);

    std::cout << "Done!" << std::endl;

    return 0;
}
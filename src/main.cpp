#include "iterator.hpp"
#include "loader.hpp"

#include <CLI11.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <string>

int main (int argc, char **argv) 
{
    Arguments args;

    args.primitive_size = 30;
    args.iters = 20000000;
    args.frames = 1;
    args.palette = 3;
    args.show_image = true;
    args.anti_aliasing = true;
    args.filename = "../examples/default.jpg";

    CLI::App app("Polygons");
        app.add_option("--primitives,-p", args.primitive_size, "Primitive size in pixels. (default: 30)");
        app.add_option("--iterations,-i", args.iters, "Number of iterations to complete (default 10000000)");
        app.add_option("--frames,-x", args.frames, "Number of frames to render (default: 1)");
        app.add_option("--palette,-c", args.palette, "The color palette to use. (default: 3");        
        app.add_option("--show,-s", args.show_image, "Show result when iterations have completed. (default: false)");
        app.add_option("--antialiasing,-a", args.anti_aliasing, "Use anti-aliasing (default: true)");
        app.add_option("--filename,-f", args.filename, "Filename.");
        //app.add_option("--distance,-d", dist_func, "The distance function to use (default: euclidean)")

    CLI11_PARSE(app, argc, argv);

    cv::Mat img = load_image(args.filename);
    std::cout << "Iterating over: " << args.filename << std::endl;

    iterate(img, args);
    
    std::cout << "Done!" << std::endl;

    return 0;
}
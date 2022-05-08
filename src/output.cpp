#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "output.hpp"

void output_to_console(int &i , int &iters) 
{
    float pct = (float(i) / float(iters));
    int barwidth = pct * 20;
    int prog = 20 - barwidth;

    std::cout << "[";

    for (int i = 0; i < barwidth; i++) {
        std::cout << "#";
    }
    for (int j = 0; j < prog; j++) {
        std::cout << " ";
    }
    std::cout << "] : " << int(pct * 100) << "%\r";
    std::cout.flush();
}

void finished_frame(int f, int frames, cv::Mat img)
{
    std::cout << std::endl;
    std::cout << "Finished frame: " << f + 1 << " of " << frames << std::endl;

    std::string filename = "output/f" + std::to_string(f) + ".jpg";
    cv::imwrite(filename, img);
}
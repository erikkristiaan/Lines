#pragma once

#include <opencv2/imgcodecs.hpp>

void output_to_console(int &i, int &iters);
void finished_frame(int f, int frames, cv::Mat img);
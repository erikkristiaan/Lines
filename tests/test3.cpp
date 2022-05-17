#include <opencv2/opencv.hpp>

#include <iostream>

cv::Point2i get_first_point(int &height, int &width)
{
    // return random (x,y) point from the canvas
    return cv::Point2i(rand() % width + 1, rand() % height + 1);
}

cv::Point2i get_second_point(int &height, int &width, int &line_length, cv::Point2i &point1)
{
    using std::pow;
    using std::sqrt;
    using std::floor;

    int x1 = point1.x;
    int y1 = point1.y;
    int x2;
    int y2;

    int x1_min = point1.x - line_length;
    int x1_max = point1.x + line_length;

    // int y_min = point1.y - line_length;
    // int y_max = point1.y + line_length;

    x2 = rand() % (x1_max - x1_min + 1) + x1_min;
    bool is_pos = rand() % 2;

    if (is_pos)
    {
        y2 = floor( sqrt( pow(line_length,2) - pow(x2 - x1,2) ) + y1 );
    }
    else
    {
        y2 = floor( -sqrt( pow(line_length,2) - pow(x2 - x1,2) ) + y1 );        
    }


    if (x2 < 0) {x2 = 0;}
    if (x2 > width) {x2 = width;}

    if (y2 < 0) {y2 = 0;}
    if (y2 > height) {y2 = height;}

    return cv::Point2i(x2, y2);
}

int main()
{
    srand(time(NULL));
    std::string filepath = cv::samples::findFile("../examples/default2.jpg");
    cv::Mat img = cv::imread(filepath, cv::IMREAD_COLOR);

    int height = img.size().height;
    int width = img.size().width;
    int ll = 30;

    cv::Point2i p1(50,50);
    auto p2 = get_second_point(height, width, ll, p1);

    std::cout << p1 << " : " << p2 << std::endl;

    return 0;
}
#include <opencv2/opencv.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>


std::array<uchar, 3> random_sample(std::vector<std::array<uchar, 3>> &vec)
{

    int index = rand() % vec.size();
    auto sample = vec[index];

    return sample;
}


std::vector<std::array<uchar, 3>> remove_duplicates(std::vector<std::array<uchar, 3>> vec)
{
    // runs in O(n log n) time but only needs to run once. Maybe refactor?
    std::vector<std::array<uchar, 3>> output;
    std::sort(vec.begin(), vec.end());

    auto it = std::unique(vec.begin(), vec.end());
    vec.resize(std::distance(vec.begin(), it));

    return vec;
}


int main()
{
    srand(time(NULL));

    std::string filepath = cv::samples::findFile("default2.jpg");
    cv::Mat img = cv::imread(filepath, cv::IMREAD_COLOR);

    int height = img.size().height;
    int width = img.size().width;

    std::vector<std::array<uchar, 3>> myVec;


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uchar R = img.at<cv::Vec3b>(y,x)[0];
            uchar G = img.at<cv::Vec3b>(y,x)[1];            
            uchar B = img.at<cv::Vec3b>(y,x)[2];

            myVec.push_back({R, G, B});
        }
    }

    myVec = remove_duplicates(myVec);
    random_sample(myVec);

    // std::cout << int(x[0]) << int(x[1]) << int(x[2]) << std::endl; 

    for (int i = 0; i < 20000; ++i) {
        auto curr = random_sample(myVec);
        std::cout << "[" << int(curr[0]) << ", " << int(curr[1]) << ", " << int(curr[2]) << "]" << std::endl;        
    }

    // returns full list of colors
    // for (auto it = myVec.begin(); it != myVec.end(); ++it) {
    //     std::array<uchar, 3> curr = *it;
    //     std::cout << "[" << int(curr[0]) << ", " << int(curr[1]) << ", " << int(curr[2]) << "]" << std::endl;
    // }


    return 0;
}
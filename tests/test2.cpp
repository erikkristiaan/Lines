#include <opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>


#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>

template<typename T>
T random_s(std::set<T> const &s)
{
    srand(time(NULL));
    auto it = s.begin();
    int idx = rand() % s.size();
    std::advance(it, idx);
    return *it;
}

int main()
{
    // std::set<std::vector<uchar>> myset;
    // std::vector<uchar> myvec = {255,255,255};

    // myset.insert(myvec);

    // // auto it = myset.begin();

    // std::cout << myset << std::endl;

    // for (int i = 0; i < myset.size(); ++i) {
    //     std::cout << myset[i](0) << std::endl;

    // }

    // return 0;
    std::vector<cv::Vec3b> myset;

    cv::Vec3b myvec(255,255,255);

    myset.push_back(myvec);
    // myset.insert({110,110,110});
    // myset.insert({0,0,0});
    // myset.insert({255,255,255});

    std::cout << myset[0] << std::endl;
    return 0;
}
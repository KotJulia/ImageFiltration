#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

class Thresholding {

    double arithmeticAverage(int i, int j, cv::Mat image, int windowSize);

    double geometricAverage(int i, int j, cv::Mat image, int windowSize);

    double median(int i, int j, cv::Mat image, int windowSize);

public:
    cv::Mat thresholding(cv::Mat image, int thresholdType, int windowSize);
};

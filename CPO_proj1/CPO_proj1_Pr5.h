#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

class Thresholding {

    // Calculates threshold as arithmetic mean of given surroundings
    double arithmeticAverage(int i, int j, cv::Mat image, int windowSize);

    // Calculates threshold as geometric mean of given surroundings
    double geometricAverage(int i, int j, cv::Mat image, int windowSize);

    // Calculates threshold as median of given surroundings
    double median(int i, int j, cv::Mat image, int windowSize);

public:
    // Returns binary image after thresholding
    cv::Mat thresholding(cv::Mat image, int thresholdType, int windowSize);
};

#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>


int main()
{
    cv::Mat image = cv::imread("C:\\Users\\user\\OneDrive\\Pulpit\\obraz711.jpg", cv::IMREAD_GRAYSCALE);
    int colorScale[255] = { };
    int color;
    int sum = 0;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            color = (int)image.at<uchar>(i, j);
            colorScale[color] += 1;
        }
    }
    for (int i = 0; i < sizeof(colorScale); i++) {
        sum += colorScale[i];
    }
    std::cout << sum;
}

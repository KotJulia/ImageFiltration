#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

class Thresholding {

    double arithmeticAverage(int i, int j, cv::Mat image, int windowSize) {
        double sum = 0;
        int numOfPixels = 0;
        for (int x = i - (windowSize - 1) / 2; x <= i + (windowSize - 1) / 2; x++) {
            if (x < 0 || x >= image.rows) {
                continue;
            }
            for (int y = j - (windowSize - 1) / 2; y <= j + (windowSize - 1) / 2; y++) {
                if (y < 0 || y >= image.cols) {
                    continue;
                }
                sum += image.at<uchar>(x, y);
                numOfPixels += 1;
            }
        }
        double arithmeticAverage = sum / numOfPixels;
        return arithmeticAverage;
    }

    double geometricAverage(int i, int j, cv::Mat image, int windowSize) {
        double sum = 0;
        int numOfPixels = 0;
        for (int x = i - (windowSize - 1) / 2; x <= i + (windowSize - 1) / 2; x++) {
            if (x < 0 || x >= image.rows) {
                continue;
            }
            for (int y = j - (windowSize - 1) / 2; y <= j + (windowSize - 1) / 2; y++) {
                if (y < 0 || y >= image.cols || image.at<uchar>(x, y) <= 0) {
                    continue;
                }
                sum += log(image.at<uchar>(x, y));
                numOfPixels += 1;
            }
        }


        double geometricAverage = exp(sum / numOfPixels);
     
        return geometricAverage;
    }


    double median(int i, int j, cv::Mat image, int windowSize) {
        std::vector<int> listOfElements;
        for (int x = i - (windowSize - 1) / 2; x <= i + (windowSize - 1) / 2; x++) {
            if (x < 0 || x >= image.rows) {
                continue;
            }
            for (int y = j - (windowSize - 1) / 2; y <= j + (windowSize - 1) / 2; y++) {
                if (y < 0 || y >= image.cols) {
                    continue;
                }
                listOfElements.push_back(image.at<uchar>(x, y));
            }
        }
        sort(listOfElements.begin(), listOfElements.end());
        int middle_index = listOfElements.size() / 2;
        int middle_index_plus = middle_index + 1;
        double median = listOfElements.size() % 2 == 0 ? listOfElements[middle_index] : listOfElements[middle_index_plus];

        return median;
    }

public:

    cv::Mat thresholding(cv::Mat image, int thresholdType, int windowSize){
        double threshold = 0;
        cv::Mat imageThresholded = image.clone();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {

                switch (thresholdType) {
                case 0:
                    threshold = arithmeticAverage(i, j, image, windowSize);
                    break;

                case 1:
                    threshold = geometricAverage(i, j, image, windowSize);
                    break;
                case 2:
                    threshold = median(i, j, image, windowSize);
                    break;
                }
                
                if (image.at<uchar>(i, j) < threshold) {
                    imageThresholded.at<uchar>(i, j) = 0;
                }
                else {
                    imageThresholded.at<uchar>(i, j) = 255;
                }
            }
        }
        return imageThresholded;

    }
};

int main()
{
    //cv::Mat image = cv::imread("C:\\Users\\user\\OneDrive\\Pulpit\\ErrorMsg.jpg", cv::IMREAD_GRAYSCALE);

    //cv::Mat image3 = cv::imread("C:\\Users\\user\\OneDrive\\Pulpit\\animeDziewczynka.jpg", cv::IMREAD_GRAYSCALE);

    cv::Mat image4 = cv::imread("C:\\Users\\user\\OneDrive\\Pulpit\\pobrane.jpg", cv::IMREAD_GRAYSCALE);

    Thresholding image2;
   /* cv::Mat newImage = image2.thresholding(image, 0, 25);
    cv::Mat newImage2 = image2.thresholding(image, 1, 25);
    cv::Mat newImage3 = image2.thresholding(image, 2, 25);*/

   /* cv::Mat newImage4 = image2.thresholding(image3, 0, 25);
    cv::Mat newImage5 = image2.thresholding(image3, 1, 25);
    cv::Mat newImage6 = image2.thresholding(image3, 2, 25);*/


    //cv::Mat newImage7 = image2.thresholding(image4, 0, 25);
    cv::Mat newImage8 = image2.thresholding(image4, 1, 15);
    //cv::Mat newImage9 = image2.thresholding(image4, 2, 25);

    /*cv::Mat newImage4 = image2.thresholding(image, 0, 30);
    cv::Mat newImage5 = image2.thresholding(image, 1, 30);
    cv::Mat newImage6 = image2.thresholding(image, 2, 30);*/

    cv::namedWindow("Test");
    //cv::imshow("Test", image);
    cv::waitKey(0);
}

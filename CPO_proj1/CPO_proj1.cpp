#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

class Histogram {

public:

    cv::Mat createHistogram(cv::Mat image) {
        cv::Mat histogram;
        image.convertTo(image, CV_32F);
        histogram = cv::Mat::zeros(256, 1, CV_32F);
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                int level = 0;
                level = image.at<float>(i, j);
                histogram.at<float>(level) += 1;
            }
        }
        return histogram;
    }

    void plotHistogram(cv::Mat histogram) {
        cv::Mat histogram_image(400, 512, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::Mat normalized_histogram;
        normalize(histogram, normalized_histogram, 0, 400, cv::NORM_MINMAX, -1, cv::Mat());

        for (int i = 0; i < 256; i++) {
            rectangle(histogram_image, cv::Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)),
                cv::Point(2 * (i + 1), histogram_image.rows), cv::Scalar(255, 0, 0));
        }

        cv::namedWindow("Histogram", cv::WINDOW_NORMAL);
        cv::imshow("Histogram", histogram_image);
    }
};

class EqualizedHistogram: public Histogram {

public:

    void histogramEqualization(cv::Mat image, cv::Mat histogram) {
        image.convertTo(image, CV_32F);
        float probabilityDistr[255] = {};
        float CDF = 0.0;
        float newColorVal;
        float allPixels = image.rows * image.cols;

        for (int k = 0; k < 255; k++) {
            probabilityDistr[k] = histogram.at<float>(k) / allPixels;
            CDF += probabilityDistr[k];
            newColorVal = round(CDF * 255);
            for (int i = 0; i < image.rows; i++) {
                for (int j = 0; j < image.cols; j++) {
                    if (image.at<float>(i, j) == k) {
                        image.at<float>(i, j) = newColorVal;
                    }
                }
            }
        }
    }
};

int main()
{
    cv::Mat image = cv::imread("C:\\Users\\user\\OneDrive\\Pulpit\\R.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat imageGray = image.clone();
//    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

    Histogram H1;
    EqualizedHistogram H2;
    cv::Mat hist = H1.createHistogram(image);
    H1.plotHistogram(hist);
   // H2.histogramEqualization(imageGray, hist);
    //cv::Mat newHist = H2.createHistogram(imageGray);
    //H2.plotHistogram(newHist);

    cv::namedWindow("Test");
    cv::imshow("Test", image);
    cv::waitKey(0);
}

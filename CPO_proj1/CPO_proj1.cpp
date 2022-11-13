#include "CPO_proj1_Pr5.h"

double Thresholding::arithmeticAverage(int i, int j, cv::Mat image, int windowSize) {
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

double Thresholding::geometricAverage(int i, int j, cv::Mat image, int windowSize) {
	double sum = 0;
	int numOfPixels = 0;
	for (int x = i - (windowSize - 1) / 2; x <= i + (windowSize - 1) / 2; x++) {
		if (x < 0 || x >= image.rows) {
			continue;
		}
		for (int y = j - (windowSize - 1) / 2; y <= j + (windowSize - 1) / 2; y++) {
			if (y < 0 || y >= image.cols ) {
				continue;
			}
			sum += log(image.at<uchar>(x, y));
			numOfPixels += 1;
		}
	}


	double geometricAverage = exp(sum / numOfPixels);

	return geometricAverage;
}


double Thresholding::median(int i, int j, cv::Mat image, int windowSize) {
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
	int median = listOfElements.size() % 2 == 0 ? listOfElements[middle_index] : listOfElements[middle_index_plus];

	return median;
}


cv::Mat Thresholding::thresholding(cv::Mat image, int thresholdType, int windowSize) {
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


int main()
{
    //cv::Mat image = cv::imread("ErrorMsg.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image = cv::imread("Kruszynka.jpeg", cv::IMREAD_GRAYSCALE);
	cv::Mat image = cv::imread("book2.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image = cv::imread("sea.jpg", cv::IMREAD_GRAYSCALE);


    Thresholding image2;

    cv::Mat newImageArithmetic = image2.thresholding(image, 0, 23);
    cv::Mat newImageGeometric = image2.thresholding(image, 1, 23);
    cv::Mat newImageMedian = image2.thresholding(image, 2, 23);

    while (true)
    {
		cv::namedWindow("Original image");
		cv::imshow("Original image", image);
		
		cv::namedWindow("Arithmetic mean");
		cv::imshow("Arithmetic mean", newImageArithmetic);

		cv::namedWindow("Geometric mean");
		cv::imshow("Geometric mean", newImageGeometric);

		cv::namedWindow("Median");
		cv::imshow("Median", newImageMedian);

        int key = cv::waitKey(0);
        if (key == 'q')
        {
            std::cout << "q key is pressed by the user. Stopping the video" << std::endl;
            break;
        }
	}

}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>





int main() {

	std::string imgPath = "megaman.png";

	cv::Mat image = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
	//cv::cvtColor(image,)
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	if (!image.data)
	{
		std::cout << "Image not loaded";
		return -1;
	}
	cv::imshow("Display window", image);
	std::cout << "image size:" << image.size;
	
	cv::waitKey(0);
	

	return 0;
}
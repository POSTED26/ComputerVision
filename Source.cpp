#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>



int main() {
	// Load the Caffe model
    std::string modelPath = "/Users/nobetw-m4/opencv_models/res10_300x300_ssd_iter_140000.caffemodel";
    std::string configPath = "/Users/nobetw-m4/opencv_models/deploy.prototxt";

	cv::dnn::Net net = cv::dnn::readNetFromCaffe(configPath, modelPath);
	if (net.empty()) {
		std::cerr << "Error: Could not load Caffe model!" << std::endl;
		return -1;
	}

	cv::VideoCapture cap(0); // Opens webcam, where 0 is default camera device
	if (!cap.isOpened()) {
		std::cout << "Error opening video stream or file" << std::endl;
		return -1;
	}

	cv::Mat frame;
	while (true) {
		cap >> frame; // Capture frame-by-frame
		if (frame.empty()) {
			std::cout << "End of video stream" << std::endl;
			break;
		}

        // Convert to blob (preprocessing)
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0), false, false);
        net.setInput(blob);
        cv::Mat detections = net.forward();

        // Process detections
        cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
        for (int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);
            if (confidence > 0.5) { // Confidence threshold
                int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

                // Draw bounding box
                cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);
                cv::putText(frame, "Face", cv::Point(x1, y1 - 5), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
            }
        }

        // Show the result
        cv::imshow("DNN Face Detection", frame);

		// Break when ESC key is pressed
		if (cv::waitKey(1) == 27) {
			break;
		}
	}

	cap.release();
	cv::destroyAllWindows();
	return 0;
}
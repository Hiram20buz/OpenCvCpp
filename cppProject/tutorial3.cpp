#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Read an image
    cv::Mat image = cv::imread("/Users/rxs0523/OpenCvCpp/cppProject/image.jpeg");

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Rotate the image clockwise by 45 degrees
    double angle = 45.0;
    cv::Point2f center(static_cast<float>(image.cols / 2), static_cast<float>(image.rows / 2));
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());

    // Display the original and rotated images
    cv::imshow("Original Image", image);
    cv::imshow("Rotated Image", rotatedImage);
    cv::waitKey(0);

    // Read a video
    cv::VideoCapture cap("/Users/rxs0523/OpenCvCpp/cppProject/video.mp4");

    if (!cap.isOpened()) {
        std::cout << "Could not open or find the video!" << std::endl;
        return -1;
    }

    // Create a VideoWriter object to save the rotated video
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter video("output_video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
                          cv::Size(frame_width, frame_height));

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        // Rotate each frame of the video clockwise by 90 degrees
        cv::Mat rotatedFrame;
        cv::warpAffine(frame, rotatedFrame, rotationMatrix, frame.size());

        // Display and write the rotated frame to the output video
        cv::imshow("Rotated Video", rotatedFrame);
        video.write(rotatedFrame);

        if (cv::waitKey(25) == 27) // Press 'Esc' key to exit
            break;
    }

    // Release the VideoCapture and VideoWriter objects
    cap.release();
    video.release();

    cv::destroyAllWindows();

    return 0;
}

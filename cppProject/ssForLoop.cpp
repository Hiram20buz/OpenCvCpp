#include <ApplicationServices/ApplicationServices.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

int main() {
    // Create the output folder if it doesn't exist
    std::error_code error;
    std::filesystem::create_directory("output", error);
    if (error) {
        std::cerr << "Error creating output directory: " << error.message() << std::endl;
        return -1;
    }

    // Take 10 screenshots
    for (int i = 0; i < 10; ++i) {
        CGImageRef screenShot = CGDisplayCreateImage(CGMainDisplayID());

        if (!screenShot) {
            std::cerr << "Error: Could not capture screenshot" << std::endl;
            return -1;
        }

        // Convert CGImageRef to OpenCV Mat
        size_t width = CGImageGetWidth(screenShot);
        size_t height = CGImageGetHeight(screenShot);
        cv::Mat image(height, width, CV_8UC4);

        CGDataProviderRef provider = CGImageGetDataProvider(screenShot);
        CFDataRef data = CGDataProviderCopyData(provider);
        CFIndex length = CFDataGetLength(data);
        if (length != image.total() * image.elemSize()) {
            std::cerr << "Error: Image data size mismatch" << std::endl;
            CFRelease(data);
            CGImageRelease(screenShot);
            return -1;
        }
        memcpy(image.data, CFDataGetBytePtr(data), length);
        CFRelease(data);
        CGImageRelease(screenShot);

        // Save the image as PNG in the output folder
        std::string filename = "output/screenshot_" + std::to_string(i + 1) + ".png";
        bool success = cv::imwrite(filename, image);

        if (!success) {
            std::cerr << "Error: Could not save screenshot " << filename << std::endl;
            return -1;
        }
    }

    std::cout << "10 screenshots saved in the 'output' folder" << std::endl;
    return 0;
}
/*
g++ -o ssForLoop ssForLoop.cpp -framework ApplicationServices `pkg-config --cflags --libs opencv4` -std=c++17
*/
#include <ApplicationServices/ApplicationServices.h>
#include <opencv2/opencv.hpp>

int main() {
    CGImageRef screenShot = CGDisplayCreateImage(CGMainDisplayID());

    if (!screenShot) {
        std::cerr << "Error: Could not capture screenshot" << std::endl;
        return -1;
    }

    // Convert CGImageRef to OpenCV Mat (alternative method)
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

    // Save the image as PNG
    bool success = cv::imwrite("screenshot.png", image);

    if (!success) {
        std::cerr << "Error: Could not save screenshot" << std::endl;
        return -1;
    }

    std::cout << "Screenshot saved as screenshot.png" << std::endl;
    return 0;
}

//How to compile
/*
g++ -o screenshot screenshot.cpp -framework ApplicationServices `pkg-config --cflags --libs opencv4` -std=c++11
*/

//How to run
/*
./screenshot
*/
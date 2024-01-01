#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // Open the default camera (index 0)
    VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera" << endl;
        return -1;
    }

    // Get the default resolution of the camera
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    // Define the codec and create a VideoWriter object
    VideoWriter video("output_video.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, Size(frame_width, frame_height));

    if (!video.isOpened()) {
        cerr << "Error: Could not create video file" << endl;
        return -1;
    }

    // Create a window to display the camera feed
    namedWindow("Camera Feed", WINDOW_NORMAL);

    int recordingTime = 10; // Duration in seconds
    int framesPerSecond = 30; // Frames per second

    int frameCount = 0;
    int totalFrames = recordingTime * framesPerSecond;

    while (frameCount < totalFrames) {
        Mat frame;
        // Capture frame-by-frame from the camera
        cap >> frame;

        // Check if the frame was captured successfully
        if (frame.empty()) {
            cerr << "Error: Blank frame captured from camera" << endl;
            break;
        }

        // Write the frame into the video file
        video.write(frame);

        // Display the frame in the window
        imshow("Camera Feed", frame);

        // Increment frame count
        frameCount++;

        // Break the loop if 'q' is pressed
        if (waitKey(1000 / framesPerSecond) == 'q') {
            break;
        }
    }

    // Release the VideoCapture and VideoWriter resources
    cap.release();
    video.release();

    // Close all OpenCV windows
    destroyAllWindows();

    return 0;
}

# Setup for Mac Os

## Visual Studio Code
https://code.visualstudio.com/download

## C ++
Check if cpp is already installed

### Check Compiler: 
Type the following command and press Enter:
```
g++ --version
```
This command checks if the GNU Compiler Collection for C++ (g++) is installed and displays its version if it is available. 

If it's installed, you'll see information about the installed version. If it's not installed, you'll likely get a message indicating that the command is not found or installed.

### Xcode Command Line Tools:
If you don't have the GNU Compiler Collection installed, you might need to install Xcode Command Line Tools. To do this, type the following command in the Terminal and press Enter:
```
xcode-select --install
```
This command will prompt you to install the Xcode Command Line Tools if they are not already installed. Follow the on-screen instructions to complete the installation.

Once you've followed these steps, you should have the necessary C++ compiler installed on your Mac, and you can start writing and compiling C++ programs using the Terminal.

## OpenCv
### Install OpenCV: 
If you haven't installed OpenCV yet, you can do so using Homebrew or by manually compiling from the source. Using Homebrew is the simpler method:

Open Terminal and execute the following commands:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install opencv

```
## Install CMake
```
brew install cmake
```

## Create a folder on your desktop or wherever you want
Go to desktop and create a folder manually or using the terminal
```
mkdir cppProject
```
Drag and drop the folder into visual studio code

Create a file inside the folder: tutorial.cpp

Create a file name : CMakeLists.txt
```
touch CMakeLists.txt
```
<img width="815" alt="Screen Shot 2023-12-03 at 22 21 21" src="https://github.com/Hiram20buz/OpenCvCpp/assets/112133798/2aefd327-26b0-4c6b-a011-5f5413325479">

### CMakeLists.txt must contain this ....
```
cmake_minimum_required(VERSION 3.10)
project(MyProject)
find_package(OpenCV REQUIRED)
add_executable(MyProject tutorial.cpp)
target_link_libraries(MyProject ${OpenCV_LIBS})
```

<img width="1041" alt="Screen Shot 2023-12-03 at 22 23 07" src="https://github.com/Hiram20buz/OpenCvCpp/assets/112133798/adcd0b38-218e-4670-8586-107ce1887645">

## Now run the next commands

```
mkdir build
cd build
cmake ..
```

Now save this code inside the tutorial.cpp
```
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    // Load the video file
    VideoCapture cap("video.mp4");

    // Check if the video file was opened successfully
    if (!cap.isOpened()) {
        cerr << "Error: could not open video file" << endl;
        return -1;
    }

    // Create a window to display the video frames
    namedWindow("Video", WINDOW_NORMAL);

    // Loop over the video frames and display them in the window
    while (true) {

        // Read the next frame from the video file
        Mat frame;
        cap.read(frame);

        // Check if the frame was read successfully
        if (frame.empty()) {
            break;
        }

        // Display the current frame in the window
        imshow("Video", frame);

        // Wait for a key press (or 30 milliseconds) to allow the frame to be displayed
        if (waitKey(30) >= 0) {
            break;
        }
    }

    // Release the video file and destroy the window
    cap.release();
    destroyAllWindows();

    return 0;
}
```

## Finally
```
make
./MyProject
```
## This is the whole Sequence 
```
mkdir build
cd build
cmake ..
make
./MyProject
```
Do the "make" command AFTER you have pasted the code into the script and have saved it.

## Result
<img width="1670" alt="Screen Shot 2023-12-03 at 22 41 31" src="https://github.com/Hiram20buz/OpenCvCpp/assets/112133798/fbbd3c39-8680-442e-87fd-4e923311254f">

<img width="1010" alt="Screen Shot 2023-12-03 at 22 42 47" src="https://github.com/Hiram20buz/OpenCvCpp/assets/112133798/44f32576-12cf-4371-af14-51c2238e5975">

## Resources
```
How to Setup OpenCV for C++ on Visual Studio Code (MacOS)
https://www.youtube.com/watch?v=Ozc3zWJ_NhQ
https://github.com/Infatoshi/opencv-setup/tree/main/opencv-setup

Step-by-Step Guide: Installing OpenCV C++ and Setting It Up in Visual Studio Code with CMake
https://www.youtube.com/watch?v=m9HBM1m_EMU&list=PLkmvobsnE0GHMmTF7GTzJnCISue1L9fJn&index=2

How To Install OpenCV in Visual Studio Code (Mac)
https://www.youtube.com/watch?v=WPYXCetQI1k


[4 Solutions] – to fix “cmake: command not found” error in macOS, Linux and Windows
https://cloudlinuxtech.com/fix-cmake-command-not-found-error/

Sample MP4 video files
https://samplelib.com/sample-mp4.html#google_vignette

```


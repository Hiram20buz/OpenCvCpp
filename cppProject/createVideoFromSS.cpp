#include <iostream>
#include <cstdlib>

int main() {
    // Create a folder to store screenshots
    const char* createDirCommand = "mkdir screenshots_folder";
    int createDirStatus = system(createDirCommand);

    if (createDirStatus != 0) {
        std::cerr << "Error: Unable to create a folder" << std::endl;
        return -1;
    }

    // Number of screenshots to capture
    int numScreenshots = 10;

    // Loop to take multiple screenshots
    for (int i = 1; i <= numScreenshots; ++i) {
        std::string screenshotCommand = "screencapture screenshots_folder/screenshot" + std::to_string(i) + ".png";
        int status = system(screenshotCommand.c_str());

        if (status != 0) {
            std::cerr << "Error: Unable to take a screenshot" << std::endl;
            return -1;
        }

        std::cout << "Screenshot " << i << " captured and saved as 'screenshot" << i << ".png' in the folder" << std::endl;

        // Delay between taking screenshots (adjust as needed)
        std::system("sleep 1");
    }

    // Create a video from screenshots using ffmpeg (if installed)
    //const char* createVideoCommand = "ffmpeg -framerate 30 -i screenshots_folder/screenshot%d.png -c:v libx264 -pix_fmt yuv420p output_video.mp4";
    const char* createVideoCommand = "ffmpeg -framerate 5 -i screenshots_folder/screenshot%d.png -c:v libx264 -pix_fmt yuv420p output_video.mp4";
    int createVideoStatus = system(createVideoCommand);

    if (createVideoStatus != 0) {
        std::cerr << "Error: Unable to create a video" << std::endl;
        return -1;
    }

    std::cout << "Video created: output_video.mp4" << std::endl;

    return 0;
}

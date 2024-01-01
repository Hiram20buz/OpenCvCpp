#include <iostream>
#include <cstdlib>

int main() {
    // Command to take a screenshot and save it to the current directory
    const char* command = "screencapture screenshot.png"; // Save in the same directory as the executable

    // Execute the command using system()
    int status = system(command);

    if (status != 0) {
        std::cerr << "Error: Unable to take a screenshot" << std::endl;
        return -1;
    }

    std::cout << "Screenshot captured and saved as 'screenshot.png' in the current directory" << std::endl;

    return 0;
}


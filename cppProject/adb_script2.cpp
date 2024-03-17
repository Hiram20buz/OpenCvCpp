#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <thread> // Include the <thread> header for sleep_for
#include <chrono> // Include the <chrono> header for duration

void execute_adb_command(const std::string& command) {
    std::system(command.c_str());
}

void take_screenshot() {
    std::string adb_command = "adb exec-out screencap -p > screenshot.png";
    execute_adb_command(adb_command);
    std::cout << "Screenshot taken." << std::endl;
}

cv::Mat load_image(const std::string& image_path) {
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        throw std::runtime_error("Unable to load image: " + image_path);
    }
    std::cout << "Image loaded: " << image_path << std::endl;
    return image;
}

cv::Point locate_element(cv::Mat& screenshot, cv::Mat& template_image) {
    cv::Mat result;
    cv::matchTemplate(screenshot, template_image, result, cv::TM_CCOEFF_NORMED);
    cv::Point max_loc;
    cv::minMaxLoc(result, nullptr, nullptr, nullptr, &max_loc);
    std::cout << "Template matching completed." << std::endl;
    return max_loc;
}

void tap_screen(int x, int y) {
    std::string adb_command = "adb shell input tap " + std::to_string(x) + " " + std::to_string(y);
    execute_adb_command(adb_command);
    std::cout << "Tapped on the screen." << std::endl;
}

void input_text(const std::string& text) {
    std::string adb_command = "adb shell input text \"" + text + "\"";
    execute_adb_command(adb_command);
    std::cout << "Text inputted: " << text << std::endl;
}

void perform_key_event(int event_code) {
    std::string adb_command = "adb shell input keyevent " + std::to_string(event_code);
    execute_adb_command(adb_command);
    std::cout << "Key event performed." << std::endl;
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <text_to_input>" << std::endl;
            return 1;
        }
        take_screenshot();
        cv::Mat screenshot = load_image("screenshot.png");
        cv::Mat template_image = load_image("src/test/resources/scripts/textBox.png");
        cv::Point top_left = locate_element(screenshot, template_image);
        std::cout << "Top left coordinates: " << top_left << std::endl;
        tap_screen(top_left.x, top_left.y);
        tap_screen(141, 1084);
        input_text(argv[1]);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        perform_key_event(111);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // press next
        take_screenshot();
        cv::Mat screenshot1 = load_image("screenshot.png");
        cv::Mat template1 = load_image("src/test/resources/scripts/Next1.png");
        cv::Point top_left1 = locate_element(screenshot1, template1);
        std::cout << "Top left coordinates: " << top_left1 << std::endl;
        tap_screen(top_left1.x, top_left1.y);
        tap_screen(187, 1384);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

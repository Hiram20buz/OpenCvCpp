#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

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
    std::cout << "Text inputted." << std::endl;
}

void perform_key_event(int event_code) {
    std::string adb_command = "adb shell input keyevent " + std::to_string(event_code);
    execute_adb_command(adb_command);
    std::cout << "Key event performed." << std::endl;
}

int main() {
    try {
        take_screenshot();
        cv::Mat screenshot = load_image("screenshot.png");
        cv::Mat template_image = load_image("textBox.png");
        cv::Point top_left = locate_element(screenshot, template_image);
        std::cout << "Top left coordinates: " << top_left << std::endl;
        tap_screen(top_left.x, top_left.y);
        input_text("bipoh53564@nasskar.com");
        perform_key_event(111);
        // press next
        take_screenshot();
        cv::Mat screenshot1 = load_image("screenshot.png");
        cv::Mat template1 = load_image("Next.png");
        cv::Point top_left1 = locate_element(screenshot1, template1);
        std::cout << "Top left coordinates: " << top_left1 << std::endl;
        tap_screen(top_left1.x, top_left1.y);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}

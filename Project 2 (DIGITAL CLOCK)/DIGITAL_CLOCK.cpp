#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
class DigitalClock {
private:
    bool is24HourFormat;
    bool isRunning;

    void clearScreen() {
        // Use multiple newlines instead of system-specific clear commands
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }

    void displayTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        struct tm* timeInfo = localtime(&time);

        int hour = timeInfo->tm_hour;
        std::string period = "";

        // Convert to 12-hour format if needed
        if (!is24HourFormat) {
            period = (hour >= 12) ? " PM" : " AM";
            hour = (hour > 12) ? hour - 12 : hour;
            hour = (hour == 0) ? 12 : hour;
        }

        // Display current date and time
        std::cout << "===============================\n";
        std::cout << "       DIGITAL CLOCK\n";
        std::cout << "===============================\n\n";
        
        // Display date
        std::cout << "Date: "
                 << std::setfill('0') << std::setw(2) << timeInfo->tm_mday << "/"
                 << std::setfill('0') << std::setw(2) << (timeInfo->tm_mon + 1) << "/"
                 << (timeInfo->tm_year + 1900) << "\n\n";

        // Display time
        std::cout << "Time: "
                 << std::setfill('0') << std::setw(2) << hour << ":"
                 << std::setfill('0') << std::setw(2) << timeInfo->tm_min << ":"
                 << std::setfill('0') << std::setw(2) << timeInfo->tm_sec
                 << period << "\n\n";

        // Display menu
        std::cout << "Options:\n";
        std::cout << "F - Toggle 12/24 hour format\n";
        std::cout << "Q - Quit\n\n";
    }

public:
    DigitalClock() : is24HourFormat(true), isRunning(true) {}

    void run() {
        while (isRunning) {
            clearScreen();
            displayTime();

            // Check for user input without blocking
            if (std::cin.rdbuf()->in_avail()) { // Check if input is available
                char input;
                std::cin >> input;
                
                switch (toupper(input)) {
                    case 'F':
                        is24HourFormat = !is24HourFormat;
                        break;
                    case 'Q':
                        isRunning = false;
                        break;
                }
                
                // Clear any remaining input
                std::cin.ignore(10000, '\n');
            }

            // Update every second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main() {
    DigitalClock clock;
    clock.run();
    return 0;
}
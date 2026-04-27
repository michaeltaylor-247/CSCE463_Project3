#include "VibConsumer.h"

#include <iomanip>
#include <sstream>

// ----------------
// Functionality
// ----------------
std::string VibConsumer::consume(const Event& event) const {
    std::string flag = "INVALID";
    std::string range = "UNKNOWN";
    std::string action = "NONE";
    const char* color_prefix = "";
    const char* color_reset = "";

    // Vibration Reading Clasificaitons
    if(event.reading >= 1 && event.reading <= 10) {
        flag = "GREEN";
        range = "1-10";
        color_prefix = "\033[32m";
        color_reset = "\033[0m";
    }
    else if(event.reading <= 30) {
        flag = "YELLOW";
        range = "11-30";
        action = "INSPECT EQUIPMENT";
        color_prefix = "\033[33m";
        color_reset = "\033[0m";
    }
    else if(event.reading <= 50) {
        flag = "RED";
        range = "31-50";
        action = "STOP MANUFACTURING";
        color_prefix = "\033[31m";
        color_reset = "\033[0m";
    }

    // Using a stringstream to buffer the result text
    std::ostringstream output;
    output << color_prefix
           << "[VIB ]"
           << " reading = " << std::left << std::setw(5) << (std::to_string(event.reading) + "mm")
           << " | " << std::setw(8) << flag
           << " | " << action
           << color_reset;

    return output.str();
}

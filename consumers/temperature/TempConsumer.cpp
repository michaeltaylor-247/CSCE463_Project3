#include "TempConsumer.h"

#include <iomanip>
#include <sstream>

// -------------------
// Class Things
// -------------------
TempConsumer::TempConsumer() : rolling_sum_(0) {}

// -------------------
// Functionality
// -------------------
std::string TempConsumer::consume(const Event& event) {
    readings_.push_back(event.reading);
    rolling_sum_ += event.reading;

    // Window Size for Statistics is over the 10 most recent
    if(readings_.size() > 10) {
        rolling_sum_ -= readings_.front();
        readings_.pop_front();
    }

    const char* color_prefix = "";
    const char* color_reset = "";
    std::string average_field = "N/A";
    std::string status_field = "BUFFERING";

    // Using an string stream to buffer the the output
    std::ostringstream output;
    if(readings_.size() == 10) {
        double average = static_cast<double>(rolling_sum_) / static_cast<double>(readings_.size());

        std::ostringstream avg_stream;
        avg_stream << average << "F";
        average_field = avg_stream.str();

        status_field = "OK";
        color_prefix = "\033[32m";
        color_reset = "\033[0m";
        if(average > 73.0) {
            color_prefix = "\033[33m";
            color_reset = "\033[0m";
            status_field = "WARNING";
        }
    }

    output << color_prefix
           << "[TEMP]"
           << " reading = " << std::left << std::setw(5) << (std::to_string(event.reading) + "F")
           << " | " << std::setw(8) << average_field
           << " | " << status_field
           << color_reset;

    return output.str();
}

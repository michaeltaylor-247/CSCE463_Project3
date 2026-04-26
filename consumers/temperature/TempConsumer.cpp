#include "TempConsumer.h"


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

    // Using an string stream to buffer the the output
    std::ostringstream output;
    output << "[TEMPERATURE] Reading: " << event.reading << "F";

    if(readings_.size() < 10) {
        output << " | buffering window " << readings_.size() << "/10";
        return output.str();
    }

    double average = static_cast<double>(rolling_sum_) / static_cast<double>(readings_.size());
    output << " | avg(10): " << average << "F";

    if(average > 73.0) {
        output << " | WARNING: overheating threshold exceeded";
    }

    return output.str();
}

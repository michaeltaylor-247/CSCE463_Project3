#include "VibConsumer.h"

#include <sstream>

// ----------------
// Functionality
// ----------------
std::string VibConsumer::consume(const Event& event) const {
    std::string flag = "INVALID";

    // Vibration Reading Clasificaitons
    if(event.reading >= 1 && event.reading <= 10) {
        flag = "GREEN";
    }
    else if(event.reading <= 30) {
        flag = "YELLOW";
    }
    else if(event.reading <= 50) {
        flag = "RED";
    }

    // Using a stringstream to buffer the result text
    std::ostringstream output;
    output << "[VIBRATION] Reading: " << event.reading << "mm | flag: " << flag;

    if(flag == "YELLOW") {
        output << " | INSPECT EQUIPMENT";
    }
    else if(flag == "RED") {
        output << " | STOP MANUFACTURING";
    }

    return output.str();
}

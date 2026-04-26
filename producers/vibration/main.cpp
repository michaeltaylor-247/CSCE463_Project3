#include <iostream>
#include <time.h>
#include <unistd.h>

#include "VibProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer sensor;

    while(true) {
        Event e = sensor.produce();

        std::string tier;
        if (e.reading <= 10) tier = "GREEN TIER";
        else if (e.reading <= 30) tier = "YELLOW TIER";
        else tier = "RED TIER";

        time_t raw = static_cast<time_t>(e.timestamp);
        std::string timeStr = ctime(&raw);
        timeStr.pop_back();  // removes '\n' that ctime() automatically inserts
        std::cout << timeStr << " " << e.reading << " [" << tier << "]" << std::endl;
        sleep(1);
    }

    return 0;
}

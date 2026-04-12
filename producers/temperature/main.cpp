
#include <iostream>
#include <time.h>
#include <unistd.h>

#include "TempProducer.h"
#include "../../utility/Event.h"

int main() {
    TempProducer sensor;

    // naive inf loop to constantly generate new data
    while(true) {
        Event e = sensor.produce();

        time_t raw = static_cast<time_t>(e.timestamp);
        std::string timeStr = ctime(&raw);
        timeStr.pop_back();  // removes '\n' that ctime() automatically inserts
        std::cout << timeStr << " " << e.reading << std::endl;
        sleep(1);
    }


    return 0;
}

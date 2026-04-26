
#include <iostream>
#include <time.h>
#include <unistd.h>

#include "TempProducer.h"
#include "../../kafka/KafkaProducer.h"
#include "../../utility/Event.h"

int main() {
    TempProducer sensor;
    KafkaProducer kafkaProducer;

    while (true) {
        Event e = sensor.produce();
        kafkaProducer.pushEvent(e);

        time_t raw = static_cast<time_t>(e.timestamp);
        std::string timeStr = ctime(&raw);
        timeStr.pop_back(); // removes '\n' that ctime() automatically inserts

        std::cout << timeStr << " [TEMPERATURE] " << e.reading << "F" << std::endl;
        sleep(1);
    }

    return 0;
}

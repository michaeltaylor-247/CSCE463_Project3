#include <iostream>
#include <time.h>
#include <unistd.h>

#include "VibProducer.h"
#include "../../kafka/KafkaProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer sensor;
    KafkaProducer kafkaProducer;

    while(true) {
        Event e = sensor.produce();
        kafkaProducer.pushEvent(e);
        
        time_t raw = static_cast<time_t>(e.timestamp);
        std::string timeStr = ctime(&raw);
        timeStr.pop_back(); // removes '\n' that ctime() automatically inserts

        std::cout << "[VIBRATION] " << timeStr << " " << e.reading << "mm" << std::endl;
        sleep(1);
    }

    return 0;
}

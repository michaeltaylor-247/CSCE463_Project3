#include <iostream>
#include <time.h>
#include <unistd.h>

#include "VibProducer.h"
#include "../../kafka/KafkaProducer.h"
#include "../../utility/Event.h"

int main() {
    // Init Sensor & KafkaClient 
    VibProducer sensor;
    KafkaProducer kafkaProducer;

    while(true) {
        Event e = sensor.produce();
        kafkaProducer.pushEvent(e);
        
        // cout for debug
        std::string tier;
        if(e.reading <= 10) tier = "GREEN TIER";
        else if(e.reading <= 30) tier = "YELLOW TIER";
        else tier = "RED TIER";

        time_t raw = static_cast<time_t>(e.timestamp);
        std::string timeStr = ctime(&raw);
        timeStr.pop_back(); // removes '\n' that ctime() automatically inserts

        std::cout << timeStr << " [VIBRATION] " << e.reading << "mm [" << tier << "]" << std::endl;
        sleep(1);
    }

    return 0;
}

#include <unistd.h>

#include "VibProducer.h"
#include "../../kafka/KafkaProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer sensor;
    KafkaProducer kafkaProducer;
    int interval_seconds = 1;
    const char* interval_env = std::getenv("PRODUCER_INTERVAL");
    if(interval_env != nullptr) {
        interval_seconds = std::atoi(interval_env);
        if(interval_seconds <= 0) {
            interval_seconds = 1;
        }
    }

    while(true) {
        Event e = sensor.produce();
        kafkaProducer.pushEvent(e);
        sleep(interval_seconds);
    }

    return 0;
}

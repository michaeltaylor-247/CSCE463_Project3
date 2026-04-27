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
        sleep(1);
    }

    return 0;
}

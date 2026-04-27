#include <unistd.h>

#include "TempProducer.h"
#include "../../kafka/KafkaProducer.h"
#include "../../utility/Event.h"

int main() {
    TempProducer sensor;
    KafkaProducer kafkaProducer;

    while(true) {
        Event e = sensor.produce();
        kafkaProducer.pushEvent(e);
        sleep(1);
    }

    return 0;
}

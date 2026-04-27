#include <csignal>
#include <iostream>

#include "../../kafka/KafkaConsumer.h"
#include "../../utility/Event.h"
#include "VibConsumer.h"


int main() {
    KafkaConsumer kafkaConsumer;
    if(!kafkaConsumer.isInitialized()) {
        return 1;
    }

    VibConsumer vibConsumer;
    Event event{};

    while(true) {
        if(kafkaConsumer.pollEvent(event)) {
            std::cout << vibConsumer.consume(event) << std::endl;
        }
    }

    return 0;
}

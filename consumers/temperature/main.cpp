#include <csignal>
#include <iostream>

#include "../../kafka/KafkaConsumer.h"
#include "../../utility/Event.h"
#include "TempConsumer.h"

int main() {
    KafkaConsumer kafkaConsumer;
    if(!kafkaConsumer.isInitialized()) {
        return 1;
    }

    TempConsumer tempConsumer;
    Event event{};

    while(true) {
        if(kafkaConsumer.pollEvent(event)) {
            std::cout << tempConsumer.consume(event) << std::endl;
        }
    }

    return 0;
}

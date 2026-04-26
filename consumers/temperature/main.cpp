#include <csignal>
#include <iostream>

#include "../../kafka/KafkaConsumer.h"
#include "../../utility/Event.h"
#include "TempConsumer.h"

namespace {
volatile std::sig_atomic_t keep_running = 1;

void handleSignal(int) {
    keep_running = 0;
}
} // namespace

int main() {
    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    KafkaConsumer kafkaConsumer;
    if(!kafkaConsumer.isInitialized()) {
        return 1;
    }

    TempConsumer tempConsumer;
    Event event{};

    while(keep_running) {
        if(kafkaConsumer.pollEvent(event)) {
            std::cout << tempConsumer.consume(event) << std::endl;
        }
    }

    return 0;
}

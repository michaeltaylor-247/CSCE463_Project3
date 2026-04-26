#include <iostream>
#include <thread>
#include <chrono>
#include "VibProducer.h"
#include "../../utility/Event.h"

int main() {
    // Get broker from environment variable set in docker-compose.yml
    const char* broker_env = std::getenv("KAFKA_BROKER");
    std::string brokers = (broker_env != nullptr) ? broker_env : "localhost:9092";

    VibProducer producer(brokers);

    while(true) {
        Event ev = producer.produce();
       
        // Send the generated event to Kafka
        producer.send(ev);

        std::string tier;
        if (ev.reading <= 10) tier = "GREEN TIER";
        else if (ev.reading <= 30) tier = "YELLOW TIER";
        else if (ev.reading >= 31 && ev.reading <= 50) tier = "RED TIER";

        std::cout << "[VIBRATION] Reading: " << ev.reading << " [" << tier << "]" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
    }
    return 0;
}

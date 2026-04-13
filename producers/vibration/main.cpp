#include <iostream>
#include <thread>
#include <chrono>
#include "VibProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer producer;
    while(true){
        Event ev = producer.produce();
        int value = ev.reading;
        std::string tier;
        if (value >= 1 && value <= 10) {
            tier = "GREEN TIER";
        } else if (value >= 11 && value <= 30) {
            tier = "YELLOW TIER";
        } else if (value >= 31 && value <= 50) {
            tier = "RED TIER";
        }
        std::string sensorType = (ev.sensor == VIBRATION) ? "VIBRATION" : "UNKNOWN";
        std::cout << "Sensor: " << sensorType << "] "
                    << "Timestamp: " << ev.timestamp << ", "
                    << "Reading: " << ev.reading << ", "
                    << "Tier: " << tier << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep for 2 seconds
    }
    return 0;
}
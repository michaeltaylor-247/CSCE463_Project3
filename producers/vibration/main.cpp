#include <iostream>
#include <thread>
#include <chrono>
#include "VibProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer producer;
    while(true){
        Event ev = producer.produce();
        std::string sensorType = (ev.sensor == VIBRATION) ? "VIBRATION" : "UNKNOWN";
        std::cout << "Sensor: " << sensorType << "] "
                    << "Timestamp: " << ev.timestamp << ", "
                    << "Reading: " << ev.reading << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep for 2 seconds
    }
    return 0;
}
#include <iostream>
#include <thread>
#include <chrono>
#include "VibProducer.h"
#include "../../utility/Event.h"

int main() {
    VibProducer producer;

    while(true) {
        Event ev = producer.produce();

        std::string tier;
        if (ev.reading <= 10) tier = "GREEN TIER";
        else if (ev.reading <= 30) tier = "YELLOW TIER";
        else if (ev.reading >= 31 && ev.reading <= 50) tier = "RED TIER";

        std::cout << "[VIBRATION] Reading: " << ev.reading << " [" << tier << "]" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
    }
    return 0;
}

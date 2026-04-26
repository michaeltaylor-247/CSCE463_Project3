#include "VibProducer.h"
#include <chrono>

VibProducer::VibProducer() : gen(std::random_device{}()) {}

Event VibProducer::produce() {
    std::uniform_int_distribution<> tierDist(1, 100);
    int roll = tierDist(gen);
    int value;

    if (roll <= 50) {
        value = std::uniform_int_distribution<>(1, 10)(gen); // 50% chance 
    } 
    else if (roll <= 90) {
        value = std::uniform_int_distribution<>(11, 30)(gen); // 40% chance 
    } 
    else {
        value = std::uniform_int_distribution<>(31, 50)(gen); // 10% chance 
    }

    // Create Assign values to the produced Event
    Event ev;
    ev.reading = value;    
    
    // Generate a simple timestamp using system clock
    ev.timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    return ev; 
}

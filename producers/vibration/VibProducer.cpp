#include "VibProducer.h"
#include <chrono>

VibProducer::VibProducer() : gen(std::random_device{}()) {
    // Generator initialized with random_device for better entropy
}

Event VibProducer::produce() {
    std::uniform_int_distribution<> tierDist(1, 100);
    int roll = tierDist(gen);
    
    int value = 0;

    // Vibration logic per requirements:
    if (roll <= 50) {
        // 50% chance: 1-10 mm 
        value = std::uniform_int_distribution<>(1, 10)(gen);
    } 
    else if (roll <= 90) {
        // 40% chance: 11-30 mm 
        value = std::uniform_int_distribution<>(11, 30)(gen);
    } 
    else {
        // 10% chance: 31-50 mm 
        value = std::uniform_int_distribution<>(31, 50)(gen);
    }

    // Create the struct and manually assign values
    Event ev;
    ev.sensor = VIBRATION; // Uses the enum from Event.h
    ev.reading = value;    // Event.h expects an int, no string conversion needed
    
    // Generate a simple timestamp using system clock
    ev.timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    return ev; 
}
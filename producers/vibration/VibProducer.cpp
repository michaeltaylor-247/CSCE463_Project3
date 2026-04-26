#include "VibProducer.h"

VibProducer::VibProducer() :
    gen(std::random_device{}()),
    tierDist(1, 100),
    lowDist(1, 10),
    mediumDist(11, 30),
    highDist(31, 50) {}

Event VibProducer::produce() {
    int roll = tierDist(gen);
    int value;

    if (roll <= 50) {
        value = lowDist(gen); // 50% chance
    } 
    else if (roll <= 90) {
        value = mediumDist(gen); // 40% chance
    } 
    else {
        value = highDist(gen); // 10% chance
    }

    time_t timestamp = time(nullptr);

    Event e = {
        timestamp,
        value
    };
    return e;
}

#include "TempProducer.h"


TempProducer::TempProducer() : 
    gen(std::random_device{}()),    // Seed mt19937 generator using random_device() ({} inits obj, () calls paren overload)
    dist(60, 80) {                  // create distribution [60, 80]
}

Event TempProducer::produce() {
    time_t timestamp = time(nullptr);

    // Create a Temperature Event (sensor reading)
    Event e = {
        Sensor::TEMPERATURE,
        timestamp,
        dist(gen)
    };
    return e;
}

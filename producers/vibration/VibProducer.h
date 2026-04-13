#ifndef VIBPRODUCER_H
#define VIBPRODUCER_H

#include "../../utility/Event.h"

#include <time.h>
#include <random>

class VibProducer {
private:
    std::mt19937 gen;                           // rng engine
    std::uniform_int_distribution<> dist;       // distribution

public:
    VibProducer();
    Event produce();
};

#endif // VIBPRODUCER_H
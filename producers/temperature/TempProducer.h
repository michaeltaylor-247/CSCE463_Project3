#ifndef TEMPPRODUCER_H
#define TEMPRODUCER_H

#include "../../utility/Event.h"

#include <time.h>
#include <random>

class TempProducer {
private:
    std::mt19937 gen;                           // rng enging
    std::uniform_int_distribution<> dist;       // distribution

public:
    TempProducer();
    Event produce();
};

#endif // TEMPPRODUCER_H

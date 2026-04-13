#ifndef VIBPRODUCER_H
#define VIBPRODUCER_H

#include "../../utility/Event.h"

#include <time.h>
#include <random>

class VibProducer {
private:
    std::mt19937 gen;                           
    std::uniform_int_distribution<> dist;

public:
    VibProducer();
    Event produce();
};

#endif // VIBPRODUCER_H
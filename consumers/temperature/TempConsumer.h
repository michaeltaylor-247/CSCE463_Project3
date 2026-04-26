#ifndef TEMPCONSUMER_H
#define TEMPCONSUMER_H

#include <deque>
#include <string>
#include <sstream>

#include "../../utility/Event.h"

class TempConsumer {
private:
    std::deque<int> readings_;
    int rolling_sum_;

public:
    TempConsumer();

    std::string consume(const Event& event);
};

#endif // TEMPCONSUMER_H

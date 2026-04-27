#ifndef VIB_CONSUMER_H
#define VIB_CONSUMER_H

#include <string>

#include "../../utility/Event.h"

/*
 * A little silly...
 * - I wantted the consumer architecture to mirror that of the producers where there's a shared kafka consumer object
 * - Reading from Kafka Broker fuctionality is decoupled from processing the sensor readings...
 *
 * As a result this class is extremely lightwieght and a little silly
*/
class VibConsumer {
public:
    std::string consume(const Event& event) const;
};

#endif // VIB_CONSUMER_H

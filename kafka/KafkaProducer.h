#ifndef KAFKA_PRODUCER_H
#define KAFKA_PRODUCER_H

#include <string>

#include <librdkafka/rdkafkacpp.h>
#include "../utility/Event.h"

class KafkaProducer {
private:
    RdKafka::Producer* producer; // Kafka producer instance
    std::string topic_;

public:
    // Class Things
    KafkaProducer();
    ~KafkaProducer();

    // Functionality
    void pushEvent(const Event& event);
    std::string serializeEvent(const Event& event);
};

#endif // KAFKA_PRODUCER_H

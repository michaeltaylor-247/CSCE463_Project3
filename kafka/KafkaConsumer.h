#ifndef KAFKA_CONSUMER_H
#define KAFKA_CONSUMER_H

#include <string>

#include <librdkafka/rdkafkacpp.h>

#include "../utility/Event.h"

class KafkaConsumer {
private:
    RdKafka::KafkaConsumer* consumer_;
    std::string topic_;

    bool deserializeEvent(const RdKafka::Message& message, Event& event) const;

public:
    KafkaConsumer();
    ~KafkaConsumer();

    bool isInitialized() const;
    bool pollEvent(Event& event, int timeout_ms = 1000);
};

#endif // KAFKA_CONSUMER_H

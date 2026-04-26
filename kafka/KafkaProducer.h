#ifndef KAFKA_PRODUCER_H
#define KAFKA_PRODUCER_H

#include <iostream>
#include <memory>

#include <librdkafka/rdkafkacpp.h>
#include "../utility/Event.h"

class KafkaProducer {
    private:
        RdKafka::Producer* producer; // Kafka Producer Instance
        RdKafka::Topic* topic_;

        
    public:
        // Class Things
        KafkaProducer();
        ~KafkaProducer();

        // Actual Functionality
        void pushEvent(Event* e);
};

#endif // KAFKA_PRODUCER_H

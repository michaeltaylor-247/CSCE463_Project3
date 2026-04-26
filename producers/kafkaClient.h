#ifndef KAFKACLIENT
#define KAFKACLIENT

#include <iostream>
#include <memory> 

#include <librdkafka/rdkafkacpp.h>
#include "../utility/Event.h"

class KafkaClient {
    private:
        RdKafka::Producer* producer; // Kafka Producer Instance
        RdKafka::Topic* topic_;

        
    public:
        // Class Things
        KafkaClient();
        ~KafkaClient();

        // Actual Functionality
        void pushEvent(Event* e);
};

#endif // KAFKACLIENT

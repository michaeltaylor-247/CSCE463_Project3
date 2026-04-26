#include "KafkaProducer.h"
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

// ---------------------
// Class Things
// ---------------------
KafkaProducer::KafkaProducer() {
    // Create Configuration Object
    RdKafka::Conf* config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    topic_ = reinterpret_cast<RdKafka::Topic*>(std::getenv("TOPIC"));

    // Create and assing producer
    std::string errorMessage;
    producer = RdKafka::Producer::create(config, errorMessage);
}


// ------------------------
// Functionality
// ------------------------
void KafkaProducer::pushEvent(Event* e) {
    producer->produce(
            topic_,                             // topic
            RdKafka::Topic::PARTITION_UA,       // partition
            RdKafka::Producer::RK_MSG_COPY,     // flags
            e,                                  // payload
            sizeof(*e),                         // payload size
            nullptr,                            // key
            0                                   // msq opaque
    );
    producer->poll(0);
}

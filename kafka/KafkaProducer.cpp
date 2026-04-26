#include "KafkaProducer.h"

#include <cstdlib>
#include <iostream>

KafkaProducer::KafkaProducer() : producer(nullptr) {
    // Read from environment and get Config Parameters
    const char* broker_env = std::getenv("KAFKA_BROKER");
    const char* topic_env = std::getenv("PRODUCER_TOPIC");

    // Check if env was valid, otherwise resort to defaults
    std::string brokers = (broker_env != nullptr) ? broker_env : "localhost:9092";
    topic_ = (topic_env != nullptr) ? topic_env : "";

    if(topic_.empty()) {
        std::cerr << "KafkaProducer requires PRODUCER_TOPIC to be set" << std::endl;
        return;
    }

    std::string error_message;
    RdKafka::Conf* config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    if(config == nullptr) {
        std::cerr << "Failed to create Kafka config" << std::endl;
        return;
    }

    if(config->set("metadata.broker.list", brokers, error_message) != RdKafka::Conf::CONF_OK) {
        std::cerr << "Kafka configuration error: " << error_message << std::endl;
        delete config;
        return;
    }

    producer = RdKafka::Producer::create(config, error_message);
    if(producer == nullptr) {
        std::cerr << "Failed to create Kafka producer: " << error_message << std::endl;
    }

    delete config;
}

KafkaProducer::~KafkaProducer() {
    if(producer != nullptr) {
        producer->flush(10000);
        delete producer;
    }
}

// ----------------
// Functionality
// ----------------
std::string KafkaProducer::serializeEvent(const Event& event) {
    return std::to_string(event.reading) + "," + std::to_string(event.timestamp);
}

void KafkaProducer::pushEvent(const Event& event) {
    // Format the Event for Kafka Broker
    std::string payload = serializeEvent(event);

    // Send Event to Kafka
    RdKafka::ErrorCode result = producer->produce(
            topic_,                                 // topic
        RdKafka::Topic::PARTITION_UA,               // parition
        RdKafka::Producer::RK_MSG_COPY,             // flags
        const_cast<char*>(payload.c_str()),         // payload
        payload.size(),                             // payload size
        nullptr,                                    // key
        0,                                          // key size
        0,                                          // timestamp
        nullptr                                     // msq_opaque
    );

    // Check if Kafka produce() failed
    if (result != RdKafka::ERR_NO_ERROR) {
        std::cerr << "Failed to produce message: " << RdKafka::err2str(result) << std::endl;
        return;
    }

    producer->poll(0);
}

#include "KafkaConsumer.h"

#include <cstdlib>
#include <iostream>
#include <vector>

// ------------------
// Class THings
// ------------------
KafkaConsumer::KafkaConsumer() : consumer_(nullptr) {
    const char* broker_env = std::getenv("KAFKA_BROKER");
    const char* topic_env = std::getenv("CONSUMER_TOPIC");
    const char* group_env = std::getenv("CONSUMER_GROUP");

    std::string brokers = (broker_env != nullptr) ? broker_env : "localhost:9092";
    std::string topic = (topic_env != nullptr) ? topic_env : "";

    if(topic.empty()) {
        std::cerr << "KafkaConsumer requires CONSUMER_TOPIC to be set" << std::endl;
        return;
    }

    std::string group_id = (group_env != nullptr) ? group_env : topic + ".group";

    std::string error_message;
    RdKafka::Conf* config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    if(config == nullptr) {
        std::cerr << "Failed to create Kafka consumer config" << std::endl;
        return;
    }

    if(config->set("metadata.broker.list", brokers, error_message) != RdKafka::Conf::CONF_OK ||
       config->set("group.id", group_id, error_message) != RdKafka::Conf::CONF_OK ||
       config->set("auto.offset.reset", "latest", error_message) != RdKafka::Conf::CONF_OK) {
        std::cerr << "Kafka consumer configuration error: " << error_message << std::endl;
        delete config;
        return;
    }

    consumer_ = RdKafka::KafkaConsumer::create(config, error_message);
    delete config;

    if(consumer_ == nullptr) {
        std::cerr << "Failed to create Kafka consumer: " << error_message << std::endl;
        return;
    }

    RdKafka::ErrorCode result = consumer_->subscribe({topic});
    if(result != RdKafka::ERR_NO_ERROR) {
        std::cerr << "Failed to subscribe to topic: " << RdKafka::err2str(result) << std::endl;
        delete consumer_;
        consumer_ = nullptr;
        return;
    }
}

KafkaConsumer::~KafkaConsumer() {
    if(consumer_ != nullptr) {
        consumer_->close();
        delete consumer_;
    }
}

// ------------------
// Functionality
// ------------------
bool KafkaConsumer::isInitialized() const {
    return consumer_ != nullptr;
}

bool KafkaConsumer::deserializeEvent(const RdKafka::Message& message, Event& event) const {
    std::string payload(static_cast<const char*>(message.payload()), message.len());
    std::size_t separator = payload.find(',');

    if(separator == std::string::npos) {
        return false;
    }

    event.reading = std::stoi(payload.substr(0, separator));
    event.timestamp = std::stoll(payload.substr(separator + 1));
    return true;
}

bool KafkaConsumer::pollEvent(Event& event, int timeout_ms) {
    if(consumer_ == nullptr) {
        std::cerr << "Kafka consumer is not initialized" << std::endl;
        return false;
    }

    RdKafka::Message* message = consumer_->consume(timeout_ms);
    if(message == nullptr) {
        return false;
    }

    bool received_event = false;
    if(message->err() == RdKafka::ERR_NO_ERROR) {
        received_event = deserializeEvent(*message, event);
    } else if(message->err() != RdKafka::ERR__TIMED_OUT &&
              message->err() != RdKafka::ERR__PARTITION_EOF) {
        std::cerr << "Kafka consumer error: " << message->errstr() << std::endl;
    }

    delete message;
    return received_event;
}

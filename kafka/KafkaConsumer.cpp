#include "KafkaConsumer.h"

#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
std::vector<std::string> splitTopics(const std::string& topics) {
    std::vector<std::string> parsed_topics;
    std::string current;

    for(char ch : topics) {
        if(ch == ',') {
            if(!current.empty()) {
                parsed_topics.push_back(current);
                current.clear();
            }
            continue;
        }

        if(ch != ' ') {
            current.push_back(ch);
        }
    }

    if(!current.empty()) {
        parsed_topics.push_back(current);
    }

    return parsed_topics;
}
} // namespace

KafkaConsumer::KafkaConsumer() : consumer_(nullptr) {
    const char* broker_env = std::getenv("KAFKA_BROKER");
    const char* topic_env = std::getenv("CONSUMER_TOPIC");
    const char* topics_env = std::getenv("CONSUMER_TOPICS");
    const char* group_env = std::getenv("CONSUMER_GROUP");

    std::string brokers = (broker_env != nullptr) ? broker_env : "localhost:9092";
    topic_ = (topic_env != nullptr) ? topic_env : "";
    if(topic_.empty() && topics_env != nullptr) {
        topic_ = topics_env;
    }

    if(topic_.empty()) {
        std::cerr << "KafkaConsumer requires CONSUMER_TOPIC or CONSUMER_TOPICS to be set" << std::endl;
        return;
    }

    std::string group_id = (group_env != nullptr) ? group_env : topic_ + ".group";

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

    std::vector<std::string> topics = splitTopics(topic_);
    if(topics.empty()) {
        std::cerr << "KafkaConsumer received an empty topic list" << std::endl;
        delete consumer_;
        consumer_ = nullptr;
        return;
    }

    RdKafka::ErrorCode result = consumer_->subscribe(topics);
    if(result != RdKafka::ERR_NO_ERROR) {
        std::cerr << "Failed to subscribe to topic(s): " << RdKafka::err2str(result) << std::endl;
        delete consumer_;
        consumer_ = nullptr;
        return;
    }

    std::cout << "Kafka consumer subscribed to: " << topic_ << std::endl;
}

KafkaConsumer::~KafkaConsumer() {
    if(consumer_ != nullptr) {
        consumer_->close();
        delete consumer_;
    }
}

bool KafkaConsumer::isInitialized() const {
    return consumer_ != nullptr;
}

bool KafkaConsumer::deserializeEvent(const RdKafka::Message& message, Event& event) const {
    std::string payload(static_cast<const char*>(message.payload()), message.len());
    std::size_t separator = payload.find(',');

    if(separator == std::string::npos) {
        std::cerr << "Skipping malformed payload: " << payload << std::endl;
        return false;
    }

    try {
        event.reading = std::stoi(payload.substr(0, separator));
        event.timestamp = std::stoll(payload.substr(separator + 1));
    } catch(const std::exception& ex) {
        std::cerr << "Failed to parse payload \"" << payload << "\": " << ex.what() << std::endl;
        return false;
    }

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
    switch(message->err()) {
        case RdKafka::ERR_NO_ERROR:
            received_event = deserializeEvent(*message, event);
            break;
        case RdKafka::ERR__TIMED_OUT:
        case RdKafka::ERR__PARTITION_EOF:
            break;
        default:
            std::cerr << "Kafka consumer error: " << message->errstr() << std::endl;
            break;
    }

    delete message;
    return received_event;
}

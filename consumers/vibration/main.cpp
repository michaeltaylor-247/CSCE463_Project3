
#include <iostream>
#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <csignal>

bool run = true;

// Handle Ctrl+C to cleanly exit
void sigterm(int sig) {
    run = false;
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);

    // Set up Kafka consumer configuration
    const char* broker_env = std::getenv("KAFKA_BROKER");
    std::string brokers = (broker_env != nullptr) ? broker_env : "localhost:9092";
    const char* topics_env = std::getenv("CONSUMER_TOPICS");
    std::string topics_str = (topics_env != nullptr) ? topics_env : "factory.sensors.vibration";
    std::vector<std::string> topics = split(topics_str, ',');

    std::string error_string;
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    // Set configuration properties for the Kafka consumer
    conf->set("metadata.broker.list", brokers, error_string);
    conf->set("group.id", "vib_consumer_group", error_string);
    conf->set("auto.offset.reset", "latest", error_string);

    // Create Kafka consumer instance
    RdKafka::KafkaConsumer* consumer = RdKafka::KafkaConsumer::create(conf, error_string);
    if (!consumer) {
        std::cerr << "Failed to create consumer: " << error_string << std::endl;
        return 1;
    }
    delete conf;

    std::cout << "Consumer started. Listening to topics: " << topics_str << std::endl;

    std::queue<int> temp_window;
    int temp_sum = 0;

    while (run) {
        RdKafka::Message *msg = consumer->consume(1000); // 1000ms timeout

        if (msg->err() == RdKafka::ERR_NO_ERROR) {
            // Extract topic and payload
            std::string topic_name = msg->topic_name();
            std::string payload(static_cast<const char*>(msg->payload()), msg->len());
            
            // Payload is "value,timestamp" based on producer
            std::vector<std::string> parsed_data = split(payload, ',');
            if (parsed_data.size() < 2) continue; // Skip malformed messages
            
            int value = std::stoi(parsed_data[0]);
            
            // --- PROCESS VIBRATION ---
            if (topic_name == "factory.sensors.vibration") {
                std::string flag;
                if (value >= 1 && value <= 10) flag = "GREEN";
                else if (value >= 11 && value <= 30) flag = "YELLOW";
                else if (value >= 31 && value <= 50) flag = "RED";
                
                std::cout << "[VIBRATION] Reading: " << value << "mm -> " << flag << std::endl;
            }
            // --- PROCESS TEMPERATURE ---
            else if (topic_name == "factory.sensors.temperature") {
                temp_window.push(value);
                temp_sum += value;

                // Maintain window size of 10
                if (temp_window.size() > 10) {
                    temp_sum -= temp_window.front();
                    temp_window.pop();
                }

                // If window is full, calculate average
                if (temp_window.size() == 10) {
                    double average = static_cast<double>(temp_sum) / 10.0;
                    std::cout << "[TEMPERATURE] Current Avg: " << average << "°F";
                    
                    if (average > 73.0) {
                        std::cout << "  *** WARNING: Overheating! ***";
                    }
                    std::cout << std::endl;
                } else {
                     std::cout << "[TEMPERATURE] Buffering... (" << temp_window.size() << "/10)" << std::endl;
                }
            }
        } 
        else if (msg->err() != RdKafka::ERR__PARTITION_EOF && msg->err() != RdKafka::ERR__TIMED_OUT) {
            std::cerr << "Consumer error: " << msg->errstr() << std::endl;
        }
        delete msg;
    }

    // Clean up
    consumer->close();
    delete consumer;
    return 0;
}

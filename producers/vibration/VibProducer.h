#ifndef VIBPRODUCER_H
#define VIBPRODUCER_H
#include <librdkafka/rdkafkacpp.h> 

#include "../../utility/Event.h"

#include <time.h>
#include <random>

class VibProducer {
private:
    std::mt19937 gen;                           // rng engine
    RdKafka::Producer* producer; // Kafka producer instance
    std::string topic = "factory.sensors.vibration"; // Kafka topic for vibration data

public:
    VibProducer(const std::string& brokers); //Constructor to initialize the Kafka producer with the given broker list
    ~VibProducer(); //Destructor to clean up the Kafka producer instance
    void send(const Event& event); //Method to send an Event object to the Kafka topic
    Event produce();
};

#endif // VIBPRODUCER_H
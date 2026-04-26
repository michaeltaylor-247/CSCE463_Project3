#include "VibProducer.h"
#include <chrono>
#include <iostream>

VibProducer::VibProducer(const std::string& brokers) {
    std::string error_string;
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL); //Create global configuration object
    //Set the broker list for the Kafka producer
    if(conf->set("metadata.broker.list", brokers, error_string) != RdKafka::Conf::CONF_OK) {
        std::cerr << "Configuration error: " << error_string << std::endl;
    }
    //Create the Kafka producer instance using the configured settings
    producer = RdKafka::Producer::create(conf, error_string);
    if (!producer) {
        std::cerr << "Failed to create producer: " << error_string << std::endl;
    }
    delete conf; //Clean up the configuration object after creating the producer
}

Event VibProducer::produce() {
    std::uniform_int_distribution<> tierDist(1, 100);
    int roll = tierDist(gen);
    int value;

    if (roll <= 50) {
        value = std::uniform_int_distribution<>(1, 10)(gen); // 50% chance 
    } 
    else if (roll <= 90) {
        value = std::uniform_int_distribution<>(11, 30)(gen); // 40% chance 
    } 
    else {
        value = std::uniform_int_distribution<>(31, 50)(gen); // 10% chance 
    }

    // Assign values to the event
    Event ev;
    ev.sensor = VIBRATION; 
    ev.reading = value;    
    
    // Generate a simple timestamp using system clock
    ev.timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    return ev; 
}

// Method to send an Event object to the Kafka topic
void VibProducer::send(const Event& event) {
    if(!producer) {
        std::cerr << "Producer not initialized" << std::endl;
        return;
    }
    std::string msg = std::to_string(event.reading) + "," + std::to_string(event.timestamp); // Create a message string from the event data
    RdKafka::ErrorCode resp = producer->produce(
        topic,                             // 1. Topic name
        RdKafka::Topic::PARTITION_UA,      // 2. Partition (Unassigned)
        RdKafka::Producer::RK_MSG_COPY,    // 3. Message flags (Copy payload)
        const_cast<char*>(msg.c_str()),    // 4. Payload pointer
        msg.size(),                        // 5. Payload size
        nullptr,                           // 6. Message Key (we don't have one)
        0,                                 // 7. Message Key length
        0,                                 // 8. Timestamp (0 = let Kafka assign it)
        nullptr                            // 9. Opaque pointer for delivery callbacks
    );
    if (resp != RdKafka::ERR_NO_ERROR) {
        std::cerr << "Failed to produce message: " << RdKafka::err2str(resp) << std::endl;
    } else {
        producer->poll(0); // Poll to handle delivery reports
    }
}

VibProducer::~VibProducer() {
    if(producer) {
        producer->flush(10000); // Wait up to 10 seconds for any outstanding messages to be delivered
        delete producer; // Clean up the producer instance
    }
}


# CSCE463 Networks - Project 3
A real time event streaming system for some arbitrary factory with sensors (temperature and vibration). 

Built using C/C++, Apache Kafka, and conatinerized. 

----
# Apach Kafka Message Schema
Apache Kafka is simply distributed event streaming platform where **publishers** write *events* (an atomic message) to a **topic** (a stream of events). A consumer would then read from the topic. 

This means that we need to specify a format/schema/contract (whatever you want to call it) that each event follows... something like this:
```cpp
// In utility/event_scheme...
typedef struct Event {
    enum sensor; // either VIBRATION or TEMPERATURE
    float time;  // time in which the event was captured
    int reading; // the virbation in millimieters or the teperature in F
}

Event e;
```

Then we can serialize the data via some standardized way of writing to and from kafka as a byte stream. This could be some `utility/messageParser` or smth...



----
Current Repo Structure:
```
├── consumers
│   ├── temperature
│   │   └── main.cpp
│   └── vibration
│       └── main.cpp
└── producers
    ├── temperature
    │   └── main.cpp
    └── vibration
        └── main.cpp

6 directories, 4 files
```
----


# Checklist
- [ ] Develop Consumers & Producers
    - [ ] Vibration Producer
    - [ ] Temperature Producer
    - [ ] Vibration Consumer
    - [ ] Temperature Consumer
- [ ] Containerize
    - [ ] Containerize producers and consumers
    - [ ] Setup Apache Kafka 
    - [ ] Link all containerized processes together 
- [ ] Testing
    - [ ] Test if system scales 
    - [ ] Distributed -- some containers on one machine, other containers on a different machine

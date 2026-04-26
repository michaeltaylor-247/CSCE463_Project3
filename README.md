
# CSCE463 Networks - Project 3
A real time event streaming system for some arbitrary factory with sensors (temperature and vibration). 

Built using C/C++, Apache Kafka, and conatinerized. 

----
#### Repo Structure:

```
.
├── CMakeLists.txt
├── Dockerfile
├── Makefile
├── README.md
├── consumers
│   ├── temperature
│   │   └── main.cpp
│   └── vibration
│       └── main.cpp
├── docker-compose.yaml
├── kafka
│   ├── KafkaProducer.cpp
│   └── KafkaProducer.h
├── producers
│   ├── temperature
│   │   ├── TempProducer.cpp
│   │   ├── TempProducer.h
│   │   ├── main.cpp
│   │   └── testing.cpp
│   └── vibration
│       ├── VibProducer.cpp
│       ├── VibProducer.h
│       └── main.cpp
└── utility
    └── Event.h
```
----



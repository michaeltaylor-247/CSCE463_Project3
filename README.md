
# CSCE463 Networks - Project 3
A real time event streaming system for some arbitrary factory with sensors (temperature and vibration). 

Built using C/C++, Apache Kafka, and conatinerized. 

----
#### Repo Structure:
```
.
├── AGENT.md
├── CMakeLists.txt
├── Makefile
├── README.md
├── config
│   ├── Config.cpp
│   └── Config.h
├── consumers
│   ├── temperature
│   │   └── main.cpp
│   └── vibration
│       └── main.cpp
├── docker_compose.yaml
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
├── specSheet.md
└── utility
    └── Event.h

9 directories, 20 files

```
----



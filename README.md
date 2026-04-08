
# CSCE463 Networks and Distrubuted Processings Project 3


**Technologies**
- Docker Conatiners
- Apache Kafka



Sensors:
- Temperature - detection of abnormal temperature readings
- Virbation - detection of abnormal vibrations

Technical Components:
- Kafka Broker; containerized
- Two different producers (one for each sensor); each producer is containerized
- Consumers; containerized 


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

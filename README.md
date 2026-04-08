
# CSCE463 Networks - Project 3
**Technologies**
- Docker Conatiners
- Apache Kafka


Sensors:
- Temperature - detection of abnormal temperature readings --> **Michael**
- Vibration - detection of abnormal vibrations --> **Evan**

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

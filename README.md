
# CSCE463 Networks - Project 3
A real time event streaming system for some arbitrary factory with sensors (temperature and vibration). 

Built using C/C++, Apache Kafka, and conatinerized. 

----
# Running Notes
Runtime configuration is stored in `.env`.
## All Containers Locally
Start the full system:

```bash
docker compose up --build
```

Stop the containers:

```bash
docker compose down
```

Stop the containers and clear Kafka's stored data:

```bash
docker compose down -v
```

## Scaling Producers / Consumers
Example:

```bash
docker compose up --build \
  --scale producer_temp=2 \
  --scale producer_vibration=2 \
  --scale consumer_temp=2 \
  --scale consumer_vibration=2
```

Check running services:

```bash
docker compose ps
```

Follow consumer logs only:

```bash
docker compose logs -f consumer_temp consumer_vibration
```

## Distributed Test
For the distributed two-machine test, update `.env` before starting containers.

> using ipv4 addresses

On the broker machine:
- set `BROKER_ADVERTISED_LISTENER=PLAINTEXT://<broker_ip>:9092`

On the producer / consumer machine:
- set `KAFKA_BROKER=<broker_ip>:9092`

Then start the stack as usual:

```bash
docker compose up --build
```

Both machines must be on the same network, and port `9092` must be reachable from the producer / consumer machine.


#### Repo Structure:

```
.
├── CMakeLists.txt
├── Dockerfile
├── Makefile
├── README.md
├── docker-compose.yaml
├── consumers
│   ├── temperature
│   │   ├── TempConsumer.cpp
│   │   ├── TempConsumer.h
│   │   └── main.cpp
│   └── vibration
│       ├── VibConsumer.cpp
│       ├── VibConsumer.h
│       └── main.cpp
├── kafka
│   ├── KafkaConsumer.cpp
│   ├── KafkaConsumer.h
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
├── utility
│   └── Event.h
└── .env
```
----


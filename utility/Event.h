#ifndef EVENT_H

#define EVENT_H

#include <cstdint>

enum Sensor {
    TEMPERATURE,
    VIBRATION
};

typedef struct Event {
    Sensor sensor;
    int64_t timestamp;
    int reading;
} Event;

#endif // EVENT_H

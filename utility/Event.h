#ifndef EVENT_H

#define EVENT_H

#include <cstdint>

typedef struct Event {
    int64_t timestamp;
    int reading;
} Event;

#endif // EVENT_H

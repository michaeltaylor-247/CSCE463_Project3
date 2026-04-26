# Project Config
cmake_minimum_required(VERSION 3.22)
project(factory_streaming LANGUAGES CXX)

# Use C++17 and keep the compiler mode consistent across targets.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json for editor tooling.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate C++ Apache Kafka Libary
find_package(PkgConfig REQUIRED)
pkg_check_modules(RDKAFKA REQUIRED IMPORTED_TARGET rdkafka++)

# Reuse the same warning flags for every target.
set(PROJECT_WARNINGS
    -Wall
    -Wextra
    -Wpedantic
)

# -------------------------------------------
# Shared libraries
# - These are shared libraries that executables need to be linked against
# - "Libraries" --> compiled things
#       - this is why "Event.h" doesn't need to be linked against; its not compiled, just a header w/declarations
# -------------------------------------------
# Link the Kafka Producer Class against the Apache Kafka Libary
add_library(kafka_producer kafka/KafkaProducer.cpp)
target_link_libraries(kafka_producer PUBLIC PkgConfig::RDKAFKA)
target_compile_options(kafka_producer PRIVATE ${PROJECT_WARNINGS})

# -----------------------------------------------------
# Executables (4 total, one for each sensor consumer/producer)
# -------------------------------------------------------

# Temperature Producer
add_executable(temp_producer
    producers/temperature/main.cpp
    producers/temperature/TempProducer.cpp
)
target_link_libraries(temp_producer PRIVATE kafka_producer)
target_compile_options(temp_producer PRIVATE ${PROJECT_WARNINGS})

# Vibration Producer
add_executable(vib_producer
    producers/vibration/main.cpp
    producers/vibration/VibProducer.cpp
)
target_link_libraries(vib_producer PRIVATE kafka_producer)
target_compile_options(vib_producer PRIVATE ${PROJECT_WARNINGS})

# Temperature Consumer
#add_executable(temp_consumer
#    consumers/temperature/main.cpp
#)

# Vibration Consumer
#add_executable(vib_consumer
#    consumers/vibration/main.cpp
#)

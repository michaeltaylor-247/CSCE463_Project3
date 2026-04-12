
# Variables
TARGET := factory
SRC_DIR := src
BUILD_DIR := build

# Compiler Flags
CXX = g++
CXXFLAGS = -std=c++17
-Wall
-Wextra
-O3

# Specify Source Direcotires
# ....
#
#
#
#
# WIP IN MAKEFILE... uh i didn't want to bother with this yet; just develop and compile manually. 

.PHONY build clean consumer producer kafka

# Make "factory" -- builds all 5 (vib producer/consumer, temp producer/consumer, kafka broker)
$(TARGET): 
	temp_producer temp_consumer vib_producer vib_consumer kafka_broker

# Per process target
temp_producer:
temp_consumer:
vib_producer:
vib_consumer:
temp_producer:

$(BUILD_DIR): $(temp

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

#  -std=c++0x

CC = g++
CFLAGS = -I ../../../gtest-1.7.0/include/ /usr/lib/libgtest.a -lpthread
all: vehicle

vehicle: main.cpp
	$(CC) $(CFLAGS) -std=c++0x main.cpp vehicle.cpp -o exe_vehicle


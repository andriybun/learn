#  -std=c++0x

CC = g++
CFLAGS = -I.

all: adapter builder composite factory prototype singleton singleton2 state

adapter: adapter.cpp
	$(CC) $(CFLAGS) -std=c++0x adapter.cpp -o exe_adapter

builder: builder.cpp
	$(CC) $(CFLAGS) builder.cpp -o exe_builder

composite: composite.cpp
	$(CC) $(CFLAGS) composite.cpp -o exe_composite

factory: factory.cpp
	$(CC) $(CFLAGS) factory.cpp -o exe_factory

prototype: prototype.cpp
	$(CC) $(CFLAGS) prototype.cpp -o exe_prototype

singleton: singleton.cpp
	$(CC) $(CFLAGS) singleton.cpp -o exe_singleton

singleton2: singleton2.cpp
	$(CC) $(CFLAGS) singleton2.cpp -o exe_singleton2

state: state.cpp
	$(CC) $(CFLAGS) -std=c++0x state.cpp -o exe_state

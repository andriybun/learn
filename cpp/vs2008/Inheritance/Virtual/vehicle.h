#pragma once

#include <cstdio>

// Compile with g++:
// g++ -I ../../../gtest-1.7.0/include/ main.cpp vehicle.cpp /usr/lib/libgtest.a -lpthread -o vehicle

//////////////////////////////////////////////////////////////////////////
// Vehicles
//////////////////////////////////////////////////////////////////////////

const int NUM_ELEMENTS = 10;

class vehicle 
{
protected:
    //int * data;
protected:
    int wheels;
    float weight;

public:
    vehicle()
    {
	printf("Vehicle: constructor\n");
	// printf("Vehicle: constructor [data = %p]\n", data);
	// data = new int[NUM_ELEMENTS];
	// data[0] = 11;
	// printf("Vehicle: created data [%p]\n", data);
    }

    vehicle(int arg)
    {
	printf("Vehicle: constructor, passed =  %d\n", arg);
    }

    virtual ~vehicle()
    {
	printf("Vehicle: destructor\n");
	// printf("Vehicle: deleting data [%p] ...", data);
	// delete [] data;
	// printf(" done\n");
    }

    virtual void print()
    {
	printf("I'm vehicle\n");
    }
};

class car : public vehicle
{
protected:
    int * data;
    int passenger_load;
public:
    car()
    {
	data = new int[NUM_ELEMENTS];
	data[0] = 12;
	printf("Car: created data [%p]\n", data);
    }
    ~car()
    {
	printf("Car: deleting data [%p] ...", data);
	delete [] data;
	printf(" done\n");
    }
    void print()
    {
	printf("I'm car\n");
    }
};

class boat : public vehicle 
{
protected:
    float depth;
public:
    boat() : vehicle(5)
    {
	printf("Boat: constructor\n");
    };
    void print()
    {
	printf("I'm boat\n");
    }
};

class amphibian : public car/*, public boat*/
{
protected:
    int * data;
public:
    amphibian()
    {
	data = new int[NUM_ELEMENTS];
	data[0] = 14;
	printf("Amphibian: created data [%p]\n", data);
    }
    ~amphibian()
    {
	printf("Amphibian: deleting data [%p] ...", data);
	delete [] data;
	printf(" done\n");
    }
    void print()
    {
	printf("I'm amphibian\n");
    }
};

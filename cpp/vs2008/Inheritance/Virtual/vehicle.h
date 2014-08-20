#pragma once

#include <cstdio>

// Compile with g++:
// g++ vehicle.cpp -o vehicle
// g++ -I ../../../gtest-1.7.0/include/ main.cpp vehicle.cpp /usr/lib/libgtest.a -lpthread -o vehicle


//////////////////////////////////////////////////////////////////////////
// Vehicles
//////////////////////////////////////////////////////////////////////////

class vehicle 
{
protected:
    int wheels;
    float weight;
public:
    virtual void print()
    {
	printf("I'm vehicle\n");
    }
};

class car : public virtual vehicle
{
protected:
    int passenger_load;
public:
    void print()
    {
	printf("I'm car\n");
    }
};

class boat : public virtual vehicle 
{
protected:
    float depth;
public:
    virtual void print()
    {
	printf("I'm boat\n");
    }
};

class amphibian : public car, public boat
{
public:
    virtual void print()
    {
	printf("I'm amphibian\n");
    }
};

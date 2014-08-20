#include "gtest/gtest.h"

#include "vehicle.h"

// TEST(vehiclesTest, testInheritance)
// {
// 	vehicle* bmw = new car;
// 	bmw->print();
// 	vehicle* bombardier = new boat;
// 	bombardier->print();
// 	vehicle* luaz = new amphibian;
// 	luaz->print();
// }

int main(int argc, char **argv)
{
    // testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();
    vehicle* bmw = new car;
    bmw->print();

    // vehicle* bombardier = new boat;
    // bombardier->print();
    // delete bombardier;
    vehicle* luaz = new amphibian;
    luaz->print();
    delete luaz;
    delete bmw;
    return 0;
}

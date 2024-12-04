#ifndef TYPES

#define TYPES 15

#include<string>
#include "floor.h"
#include "point.h"

struct instruction
{
    point movement_vector;
};

struct percept
{
    std::string label;
    int code;
    point p;
};

struct sensor_input
{
    Floor floor;
    point delta_pos;
};

// sensor_input generate_input(Floor f, point p)
// {
//     return {f, p};
// }

#endif
#pragma once
#include <set>

enum class Floor : char
{
    agent = 'A',
    clean = '.',
    dirty = '*',
    wall = 'O',
    empty = ' ' // handled just like an wall but can be used to stylize the background
};
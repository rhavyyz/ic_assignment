#pragma once

struct point
{
    int y = -1, x = -1;

    point operator +(point p)
    {
        return {p.y + y, p.x + x};
    }
    bool operator ==(point p)
    {
        return p.y == y and p.x == x;
    }

    point operator *(int i)
    {
        return {y * i, x * i};
    }
};

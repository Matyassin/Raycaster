#pragma once

#include <raylib.h>

struct Circle
{
    Vector2 Position;
    float Radius;

    Circle(float x, float y, float r)
        : Radius(r)
    {
        Position.x = x;
        Position.y = y;
    }

    Circle(Vector2 position, float r)
        : Position(position), Radius(r)
    {}

    ~Circle() = default;

    void Move(const Vector2& newPos)
    {
        Position.x = newPos.x;
        Position.y = newPos.y;
    }

    bool Contains(const Vector2& point) const
    {
        float dx = point.x - Position.x;
        float dy = point.y - Position.y;
        return (dx * dx + dy * dy) <= (Radius * Radius);
    }
};

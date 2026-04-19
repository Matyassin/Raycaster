#pragma once

#include <raylib.h>
#include "Utils.h"

struct LightRay
{
    Vector2 Start;
    float Angle;
    float Length;

    LightRay() = default;

    LightRay(Vector2 start, float l)
        : Start(start), Angle(RandomFloat(0, 2.0f * PI)), Length(l) {}

    ~LightRay() = default;

    // maybe generalized colliders?
    std::optional<float> TestIntersection(const Circle& circle) const
    {
        float dx = std::cos(Angle);
        float dy = std::sin(Angle);

        float u = Start.x - circle.Position.x;
        float v = Start.y - circle.Position.y;

        float a = dx * dx + dy * dy;
        float b = 2 * (u * dx + v * dy);
        float c = u * u + v * v - circle.Radius * circle.Radius;

        float d = b * b - 4 * a * c;

        if (d < 0)
            return {};

        d = sqrt(d);
        float x1 = (-b + d) / (2 * a);
        float x2 = (-b - d) / (2 * a);

        if (x1 >= 0 && x2 >= 0)
            return std::min(x1, x2);
        else if (x1 >= 0)
            return x1;
        else if (x2 >= 0)
            return x2;

        return {};
    }
};

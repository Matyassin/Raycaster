#pragma once

#include <raylib.h>
#include "Utils.h"

class LightRay
{
public:
    LightRay() = default;

    explicit LightRay(Vector2 start, float l)
        : m_Start(start), m_Angle(RandomFloat(0, 2.0f * PI)), m_Length(l) {}

    ~LightRay() = default;

    Vector2 GetStart() const { return m_Start; }
    float GetAngle() const { return m_Angle; }
    float GetLength() const { return m_Length; }

    void DrawRay(const Circle& followCircle, const Circle& colliderCircle, bool isRefracting, float ior)
    {
        m_Start = followCircle.GetPosition();

        auto hit = TestCollision(colliderCircle);
        Vector2 rayDir = { std::cos(m_Angle), std::sin(m_Angle) };

        if (hit.has_value() && isRefracting)
        {
            Vector2 hitPoint = {
                m_Start.x + rayDir.x * hit.value(),
                m_Start.y + rayDir.y * hit.value()
            };

            DrawLineV(m_Start, hitPoint, YELLOW);
            auto refracted = Refract(colliderCircle, hit.value(), ior);

            if (refracted.has_value())
            {
                Vector2 refractedEnd = {
                    hitPoint.x + refracted.value().x * m_Length,
                    hitPoint.y + refracted.value().y * m_Length
                };
                DrawLineV(hitPoint, refractedEnd, SKYBLUE);
            }
        }
        else
        {
            float len = m_Length;
            if (hit.has_value())
                len = hit.value();

            Vector2 end = {
                m_Start.x + rayDir.x * len,
                m_Start.y + rayDir.y * len
            };
            DrawLineV(m_Start, end, YELLOW);
        }
    }

    // Checks if the ray hit a circle.
    std::optional<float> TestCollision(const Circle& circle) const
    {
        float dx = std::cos(m_Angle);
        float dy = std::sin(m_Angle);

        float u = m_Start.x - circle.GetPosition().x;
        float v = m_Start.y - circle.GetPosition().y;

        float a = dx * dx + dy * dy;
        float b = 2 * (u * dx + v * dy);
        float c = u * u + v * v - circle.GetRadius() * circle.GetRadius();

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

    // Refracts the ray that hit a circle using Snell's law
    std::optional<Vector2> Refract(const Circle& circle, float hitDist, float ior = 1.5f) const
    {
        float dx = std::cos(m_Angle);
        float dy = std::sin(m_Angle);

        if (!hitDist)
            return {};

        Vector2 hitPoint = {
            m_Start.x + dx * hitDist,
            m_Start.y + dy * hitDist
        };
        
        Vector2 normal = {
            (hitPoint.x - circle.GetPosition().x) / circle.GetRadius(),
            (hitPoint.y - circle.GetPosition().y) / circle.GetRadius()
        };

        float cosI  = -(dx * normal.x + dy * normal.y);
        float sinT2 = (1 / ior) * (1 / ior) * (1 - cosI * cosI);

        if (sinT2 > 1)
            return {};

        float cosT = std::sqrt(1 - sinT2);

        return Vector2{
            (1 / ior) * dx + ((1 / ior) * cosI - cosT) * normal.x,
            (1 / ior) * dy + ((1 / ior) * cosI - cosT) * normal.y
        };
    }

private:
    Vector2 m_Start;
    float m_Angle;
    float m_Length;
};

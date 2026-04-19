#pragma once

#include <raylib.h>

class Circle
{
public:
    explicit Circle(float x, float y, float r)
        : m_Radius(r)
    {
        m_Position.x = x;
        m_Position.y = y;
    }

    explicit Circle(Vector2 position, float r)
        : m_Position(position), m_Radius(r) {}

    ~Circle() = default;

    Vector2 GetPosition() const { return m_Position; }
    float GetRadius() const { return m_Radius; }

    void Move(const Vector2& newPos)
    {
        m_Position.x = newPos.x;
        m_Position.y = newPos.y;
    }

    bool Contains(const Vector2& point) const
    {
        float dx = point.x - m_Position.x;
        float dy = point.y - m_Position.y;
        return (dx * dx + dy * dy) <= (m_Radius * m_Radius);
    }

private:
    Vector2 m_Position;
    float m_Radius;
};

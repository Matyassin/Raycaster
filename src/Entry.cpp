#include <print>
#include <random>

#include <raylib.h>

static float RandomFloat(float start = 0.0f, float end = 1.0f)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(start, end);

    return dist(rng);
}

struct LightRay
{
    Vector2 Start;
    float Angle;
    float Length;

    LightRay() = default;

    LightRay(Vector2 start, float l)
        : Start(start), Angle(RandomFloat(0, 2.0f * PI)), Length(l) {}

    ~LightRay() = default;
};

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
        : Position(position), Radius(r) {}

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

// maybe generalized colliders?
static std::optional<float> TestIntersection(LightRay ray, Circle circle)
{
    float dx = std::cos(ray.Angle);
    float dy = std::sin(ray.Angle);

    float u = ray.Start.x - circle.Position.x;
    float v = ray.Start.y - circle.Position.y;

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

const int MAX_RAYS = 100000;
static LightRay rays[MAX_RAYS];

int main()
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    int visibleRays = 10;

    Circle c1(screenWidth * 0.5f - 200, screenHeight * 0.5f + -200, 150);
    Circle c2(screenWidth * 0.5f + 100, screenHeight * 0.5f + 100, 200);

    Vector2 c2Speed = { 5.0f, 4.0f };

    for (int i = 0; i < MAX_RAYS; ++i)
    {
        rays[i] = LightRay(c1.Position, 10000);
    }

    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_VSYNC_HINT);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F)) ToggleBorderlessWindowed();

        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonDown(0))
            c1.Move(mousePos);

        visibleRays = std::clamp(visibleRays + static_cast<int>(GetMouseWheelMove() * MAX_RAYS * 0.05), 0, MAX_RAYS);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(c1.Position.x, c1.Position.y, c1.Radius, YELLOW);
        DrawCircle(c2.Position.x, c2.Position.y, c2.Radius, YELLOW);


        // LG logo logic
        c2.Position.x += c2Speed.x;
        c2.Position.y += c2Speed.y;
        if ((c2.Position.x >= (GetScreenWidth()  - c2.Radius)) || (c2.Position.x <= c2.Radius)) c2Speed.x *= -1.0f;
        if ((c2.Position.y >= (GetScreenHeight() - c2.Radius)) || (c2.Position.y <= c2.Radius)) c2Speed.y *= -1.0f;


        for (int i = 0; i < visibleRays; ++i)
        {
            rays[i].Start = c1.Position;

            float len = rays[i].Length;
            auto hit = TestIntersection(rays[i], c2);

            if (hit.has_value())
                len = hit.value();

            Vector2 end = {
                rays[i].Start.x + cos(rays[i].Angle) * len,
                rays[i].Start.y + sin(rays[i].Angle) * len
            };

            DrawLineV(c1.Position, end, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
}

#include <print>
#include <random>

#include <raylib.h>

#include "Circle.h"
#include "LightRay.h"

const int MAX_RAYS = 100000;
static LightRay rays[MAX_RAYS];

int main()
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    int visibleRays = 0;

    Circle c1(screenWidth * 0.5f - 200, screenHeight * 0.5f + -200, 150);
    Circle c2(screenWidth * 0.5f + 100, screenHeight * 0.5f +  100, 200);

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
        if (IsKeyPressed(KEY_F))
            ToggleBorderlessWindowed();

        if (IsKeyPressed(KEY_HOME))
            visibleRays = 0;

        if (IsKeyPressed(KEY_END))
            visibleRays = MAX_RAYS;

        if (IsMouseButtonDown(0))
            c1.Move(GetMousePosition());

        visibleRays = std::clamp(visibleRays + static_cast<int>(GetMouseWheelMove() * MAX_RAYS * 0.01), 0, MAX_RAYS);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(c1.Position.x, c1.Position.y, c1.Radius, YELLOW);
        DrawCircle(c2.Position.x, c2.Position.y, c2.Radius, YELLOW);

        for (int i = 0; i < visibleRays; ++i)
        {
            rays[i].Start = c1.Position;

            float len = rays[i].Length;
            auto hit = rays[i].TestIntersection(c2);

            if (hit.has_value())
                len = hit.value();

            Vector2 end = {
                rays[i].Start.x + cos(rays[i].Angle) * len,
                rays[i].Start.y + sin(rays[i].Angle) * len
            };

            DrawLineV(c1.Position, end, YELLOW);
        }

        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 30, GREEN);

        // LG logo
        c2.Position.x += c2Speed.x;
        c2.Position.y += c2Speed.y;
        if ((c2.Position.x >= (GetScreenWidth()  - c2.Radius)) || (c2.Position.x <= c2.Radius)) c2Speed.x *= -1.0f;
        if ((c2.Position.y >= (GetScreenHeight() - c2.Radius)) || (c2.Position.y <= c2.Radius)) c2Speed.y *= -1.0f;

        EndDrawing();
    }

    CloseWindow();
}

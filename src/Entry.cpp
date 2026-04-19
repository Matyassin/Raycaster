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
    float ior = 1.5f;
    bool isRefracting = false;

    Circle c1(screenWidth * 0.5f - 200, screenHeight * 0.5f + -200, 100);
    Circle c2(screenWidth * 0.5f + 100, screenHeight * 0.5f +  100, 200);

    Vector2 c2Speed = { 5.0f, 4.0f };

    for (int i = 0; i < MAX_RAYS; ++i)
    {
        rays[i] = LightRay(c1.GetPosition(), 10000);
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

        if (IsKeyPressed(KEY_R))
            isRefracting = !isRefracting;

        if (IsKeyPressed(KEY_UP))
            ior = std::clamp<float>((ior + 0.1f), 1, 3);
        if (IsKeyPressed(KEY_DOWN))
            ior = std::clamp<float>((ior - 0.1f), 1, 3);

        visibleRays = std::clamp<int>(visibleRays + static_cast<int>(GetMouseWheelMove() * MAX_RAYS * 0.01), 0, MAX_RAYS);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(c2.GetPosition().x, c2.GetPosition().y, c2.GetRadius(), Color{ 255, 100, 30, 255 });

        for (int i = 0; i < visibleRays; ++i)
        {
            rays[i].DrawRay(c1, c2, isRefracting, ior);
        }

        DrawCircle(c1.GetPosition().x, c1.GetPosition().y, c1.GetRadius(), ORANGE);

        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 25, GREEN);
        DrawText(TextFormat("Ray count: %d", visibleRays), 10, 50, 25, GREEN);
        DrawText(TextFormat("Index of refraction: %.1f", ior), 10, 90, 25, GREEN);
        DrawText("Press [R] to toggle refraction.", GetScreenWidth() - 400, 10, 25, GREEN);
        DrawText("Use the [UP] and [DOWN] arrows to control ior.", GetScreenWidth() - 600, 50, 25, GREEN);

        // LG logo - bouncing circle around egdes of screen
        c2.Move({ c2.GetPosition().x + c2Speed.x, c2.GetPosition().y + c2Speed.y });
        if ((c2.GetPosition().x >= (GetScreenWidth()  - c2.GetRadius())) || (c2.GetPosition().x <= c2.GetRadius())) c2Speed.x *= -1.0f;
        if ((c2.GetPosition().y >= (GetScreenHeight() - c2.GetRadius())) || (c2.GetPosition().y <= c2.GetRadius())) c2Speed.y *= -1.0f;

        EndDrawing();
    }

    CloseWindow();
}

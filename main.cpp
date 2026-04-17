#include <raylib.h>
#include <vector>
#include <string>
int main(int argc, char **argv)
{
    float sigma = 10.0f, rho = 28.0f, beta = 8.0 / 3.0f;
    if (argc == 2)
        sigma = std::stof(argv[1]);
    if (argc == 3)
        rho = std::stof(argv[2]);
    if (argc == 4)
        beta = std::stof(argv[3]);
    int fps = 90;
    int sw = 960, sh = 720;
    Camera3D camera{0};
    camera.position = Vector3{0.0f, 0.0f, 100.0f};
    camera.target = Vector3{0.0f, 0.0f, 25.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    InitWindow(sw, sh, "Lorenz Attractor");
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(fps);
    float dt = 1.0 / fps;
    Vector3 pos{1, 1, 1};
    std::vector<Vector3> points;
    float hue = 0.0f;
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        float dx = (sigma * (pos.y - pos.x)) * dt;
        float dy = (pos.x * (rho - pos.z) - pos.y) * dt;
        float dz = (pos.x * pos.y - beta * pos.z) * dt;
        pos.x += dx;
        pos.y += dy;
        pos.z += dz;
        points.emplace_back(pos.x, pos.y, pos.z);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        for (int i = 1; i < points.size(); i++)
        {
            DrawLine3D(points[i - 1], points[i], ColorFromHSV(hue, 1, 1));
        }
        DrawSphere(pos, 0.5f, WHITE);
        hue = hue > 360.0f ? 0.0f : hue + 0.1f;
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
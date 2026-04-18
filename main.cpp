#include <raylib.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
using namespace std;
void updatePos(Camera3D &camera, float theta, float phi, float p)
{
    camera.position.x = camera.target.x + p * sinf(phi) * cosf(theta);
    camera.position.y = camera.target.y + p * cosf(phi);
    camera.position.z = camera.target.z - p * sinf(phi) * sinf(theta);
}
float clamp(float val, float min, float max) { return val < min ? min : val > max ? max
                                                                                  : val; }
int main(int argc, char **argv)
{
    float sigma = 10.0f, rho = 28.0f, beta = 8.0 / 3.0f;
    if (argc == 2)
        sigma = stof(argv[1]);
    if (argc == 3)
        rho = stof(argv[2]);
    if (argc == 4)
        beta = stof(argv[3]);
    int fps = 90;
    int sw = 960, sh = 720;
    /*
        spherical to cartesian assume z-axis as upside, to change from z-axis to y-axis, (x',y',z') = (x,z,-y)
        x' = x = p*sin(phi)cos(theta)
        y' = z = p*cos(phi)
        z' = -y = -p*sin(phi)*sin(theta)
        with 3d coordinate system as y-axis upside
        theta -> rotate left/right around the object
        phi -> move up/down over the object
        p -> zoom in/out
        to orbit around (a,b,c) -> (a+x', b+y', c+z')
    */
    float theta = M_PI / 2, phi = M_PI / 2, p = 100;
    Camera3D camera{0};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    camera.target = Vector3{0.0f, 0.0f, 25.0f};
    updatePos(camera, theta, phi, p);
    InitWindow(sw, sh, "Lorenz Attractor");
    SetTargetFPS(fps);
    SetTraceLogLevel(LOG_NONE);
    float dt = 1.0 / fps;
    Vector3 pos{1, 1, 1};
    std::vector<Vector3> points;
    float hue = 0.0f;
    float sensitivity = 0.005f;
    float zoomFactor = 3.0f;
    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            // theta increases/decreases as we drag mouse to right/left
            theta = clamp(theta + delta.x * sensitivity, 0, 2 * M_PI);
            // phi is clamped between 0 and PI to prevent flipping of camera vertically
            phi = clamp(phi + delta.y * sensitivity, sensitivity, M_PI - sensitivity);
            // as p increases we zoom out
            p -= GetMouseWheelMove() * zoomFactor;
            updatePos(camera, theta, phi, p);
        }
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
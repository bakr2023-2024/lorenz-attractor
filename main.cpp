#include <raylib.h>
int main()
{
    InitWindow(960, 720, "Lorenz Attractor");
    float dt = 1.0 / GetFPS();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
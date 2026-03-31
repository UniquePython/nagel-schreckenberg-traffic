#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Nagel-Schreckenberg Traffic");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

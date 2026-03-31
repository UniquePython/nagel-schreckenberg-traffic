#include <raylib.h>

#define ROAD_LEN 300
#define MAX_VELOCTY 5
#define N_CARS 100
#define DAWDLE_PROB 0.3f

#define CELL_W 3
#define SCREEN_W (ROAD_LEN * CELL_W)
#define SCREEN_H 600 // number of history rows shown

int g_curr_road[ROAD_LEN];
int g_next_road[ROAD_LEN];

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Nagel-Schreckenberg Traffic");
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

#include <raylib.h>
#include <stddef.h>

#define ROAD_LEN 300
#define MAX_VELOCITY 5
#define N_CARS 100
#define DAWDLE_PROB 0.3f

#define CELL_W 3
#define SCREEN_W (ROAD_LEN * CELL_W)
#define SCREEN_H 600 // number of history rows shown

int g_curr_road[ROAD_LEN];
int g_next_road[ROAD_LEN];

// Returns number of empty cells ahead of position pos before hitting a car
// Must wrap around (circular road)
size_t gap_ahead(size_t pos)
{
    size_t nempty = 0;

    for (size_t d = 1; d <= MAX_VELOCITY; d++)
    {
        size_t i = (pos + d) % ROAD_LEN;

        if (g_curr_road[i] == -1)
            nempty++;
        else
            break;
    }

    return nempty;
}

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

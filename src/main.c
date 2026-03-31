#include <raylib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define ROAD_LEN 300
#define MAX_VELOCITY 5
#define N_CARS 100
#define DAWDLE_PROB 0.3f

#define CELL_W 3
#define SCREEN_W (ROAD_LEN * CELL_W)
#define SCREEN_H 600 // number of history rows shown

#define BG_COLOR BLACK

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

// ---- Color mapping ----
// -1 (empty)    → background
// 0             → red (stopped)
// MAX_VELOCITY  → green (full speed)
// in between:
//   first half  → red → yellow
//   second half → yellow → green
Color velocity_color(int velocity)
{
    if (velocity == -1)
        return BG_COLOR;

    float t = (float)velocity / MAX_VELOCITY;
    t = Clamp(t, 0.0f, 1.0f);

    if (t < 0.5f)
    {
        // Map [0, 0.5] → [0, 1]
        float local_t = t * 2.0f;
        return ColorLerp(RED, YELLOW, local_t);
    }
    else
    {
        // Map [0.5, 1] → [0, 1]
        float local_t = (t - 0.5f) * 2.0f;
        return ColorLerp(YELLOW, GREEN, local_t);
    }
}

// Applies NS rules to `road`, writes result into `next_road`
void step(void)
{
    memset(g_next_road, -1, sizeof(g_next_road));

    for (size_t pos = 0; pos < ROAD_LEN; pos++)
    {
        int velocity = g_curr_road[pos];

        if (velocity == -1)
            continue;

        // 1. Acceleration
        if (velocity < MAX_VELOCITY)
            velocity++;

        // 2. Slowing down
        size_t gap = gap_ahead(pos);
        if ((size_t)velocity > gap)
            velocity = (int)gap;

        // 3. Dawdling
        if (velocity > 0 && GetRandomValue(0, 1000) < (int)(DAWDLE_PROB * 1000))
            velocity--;

        // 4. Movement
        size_t new_pos = (pos + velocity) % ROAD_LEN;

        g_next_road[new_pos] = velocity;
    }

    memcpy(g_curr_road, g_next_road, sizeof(g_curr_road));
}

// Place N_CARS cars at random positions with random initial velocities
// Make sure no two cars occupy the same cell
void init_road(void)
{
    assert(N_CARS <= ROAD_LEN);

    memset(g_curr_road, -1, sizeof(g_curr_road));

    size_t placed = 0;

    while (placed < N_CARS)
    {
        size_t pos = GetRandomValue(0, ROAD_LEN - 1);

        if (g_curr_road[pos] == -1)
        {
            g_curr_road[pos] = GetRandomValue(0, MAX_VELOCITY);
            placed++;
        }
    }
}

int main(void)
{
    SetRandomSeed(time(NULL));

    InitWindow(SCREEN_W, SCREEN_H, "Nagel-Schreckenberg Traffic");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    init_road();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BG_COLOR);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#include <iostream>
#include <raylib.h>
int main() {
    InitWindow(800, 600, "My Raylib Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
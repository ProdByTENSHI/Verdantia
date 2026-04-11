#include <iostream>
#include <raylib.h>

int main(int argc, char** argv) {
    InitWindow(640, 480, "Test");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        EndDrawing();
    }

    return 0;
}
/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 *
 * Main module
 */

#include "orbitalSimView.hpp"

#define SECONDS_PER_DAY 86400.0F

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "EDA Orbital Simulation");

    // Camera
    Camera3D camera;
    camera.position = {10.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);

    SetCameraPanControl(MOUSE_BUTTON_LEFT);

    // Orbital simulation
    float fps = 60.0F;							  // frames per second
    float timeMultiplier = 100 * SECONDS_PER_DAY; // Simulation speed: 100 days per real second
    float timeStep = timeMultiplier / (fps*50);

    OrbitalSim sim(timeStep);
    OrbitalSim *pSim = &sim;

    // Game loop
    while (!WindowShouldClose())
    {
        // Update simulation
        pSim->updateOrbitalSim();

        // Camera
        UpdateCamera(&camera);

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        renderOrbitalSim3D(pSim);
        DrawGrid(10, 10.0f);
        EndMode3D();

        renderOrbitalSim2D(pSim);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

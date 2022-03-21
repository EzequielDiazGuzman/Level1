/*
 * Orbital simulation view
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include <time.h>
#include "orbitalSimView.hpp"

const char* getISODate(float currentTime) {
    // Epoch: 2022-01-01
    struct tm epoch_tm = { 0, 0, 0, 1, 0, 122 };
    time_t epoch = mktime(&epoch_tm);

    // Convert epoch time to local time
    time_t local_time = epoch + (time_t)currentTime;

    // Print ISO date for local time
    struct tm* local_tm = localtime(&local_time);
    return TextFormat("Date: %04d-%02d-%02d", 1900 + local_tm->tm_year, local_tm->tm_mon + 1, local_tm->tm_mday);
}

void renderOrbitalSim3D(OrbitalSim *sim)
{
    for (int i=0; i<sim->getBodiesInSym(); i++)
    {
        DrawSphere(Vector3Scale(sim->getPosition(i,false), 1E-11), 0.005F * logf(sim->getRadius(i,false)), sim->getColor(i,false));
        DrawPoint3D(Vector3Scale(sim->getPosition(i,false), 1E-11), sim->getColor(i,false));
    }
    for (int i=0; i<sim->getAsteroidsInSym(); i++)
    {
        DrawPoint3D(Vector3Scale(sim->getPosition(i, true), 1E-11), sim->getColor(i, true));
    }
}

void renderOrbitalSim2D(OrbitalSim *sim)
{
    DrawFPS(0,0);
    DrawText(getISODate(clock()), 0, 20, 14, WHITE);
}

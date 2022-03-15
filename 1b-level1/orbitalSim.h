/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "raylib-cpp.hpp"
// #include "raymath.h"

class OrbitalBody
{
    float mass;
    float radius;
    Color color;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

class OrbitalSim
{
    public:


    private:
    float timeStep;
    double timeElapsed; //getTime() is time since InitWindow()
    int bodiesInSym;
    OrbitalBody *orbitalBodies;
    int asteroidsInSym;
    OrbitalBody *asteroids;
};

OrbitalSim *makeOrbitalSim(float timeStep);
void updateOrbitalSim(OrbitalSim *sim);
void freeOrbitalSim(OrbitalSim *sim);

#endif

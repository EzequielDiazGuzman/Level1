/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

/*
 * Orbital Simulation
 *
 * 22.08 EDA
 * Level 1 - Warm Up
 *
 * Grupo 2
 * Autores: Diaz Guzman, Ezequiel & Fisher, Agustin
 * 
 * En este archivo estan declaradas las estructuras necesarias para
 * hacer la simulacion.
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "raylib.h"
#include "raymath.h"

struct OrbitalBody
{
    float mass;
    float radius;
    Color color;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

struct OrbitalSim
{
    float timeStep;
    double timeElapsed;
    int bodiesInSym;
    OrbitalBody *orbitalBodies;
    int asteroidsInSym;
    OrbitalBody *asteroids;
};

OrbitalSim *makeOrbitalSim(float timeStep);
void updateOrbitalSim(OrbitalSim *sim);
void freeOrbitalSim(OrbitalSim *sim);

#endif

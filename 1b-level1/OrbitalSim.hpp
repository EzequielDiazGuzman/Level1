/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "OrbitalBody.hpp"

class OrbitalSim
{
    public:
    OrbitalSim();
    ~OrbitalSim();

    OrbitalSim(float timeStep);

    void updateOrbitalSim();

    float timeStep;
    double timeElapsed; //getTime() is time since InitWindow()
    int bodiesInSym;
    OrbitalBody *orbitalBodies;
    int asteroidsInSym;
    OrbitalBody *asteroids;

    void updatePosition();
    void updateVelocity();
    void updateAcceleration();
    private:
};

#endif

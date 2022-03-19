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

    OrbitalBody *orbitalBodies;
    OrbitalBody *asteroids;

    void updatePosition();
    void updateVelocity();
    void updateAcceleration();

    float getTimeStep();
    int getAsteroidsInSym();
    int getBodiesInSym();

    
    private:
    int asteroidsInSym;
    int bodiesInSym;
    float timeStep;
    double timeElapsed; //getTime() is time since InitWindow()
};

#endif

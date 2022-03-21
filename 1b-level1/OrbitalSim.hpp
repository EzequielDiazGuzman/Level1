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


    void updatePosition();
    void updateVelocity();
    void updateAcceleration();

    raylib::Vector3 getPosition(int i, bool asteroid);
    raylib::Color getColor(int i, bool asteroid);
    float getRadius(int i, bool asteroid);

    float getTimeStep();
    int getAsteroidsInSym();
    int getBodiesInSym();

    
    private:
    OrbitalBody *orbitalBodies;
    OrbitalBody *asteroids;
    int asteroidsInSym;
    int bodiesInSym;
    float timeStep;
    double timeElapsed; //getTime() is time since InitWindow()
};

#endif

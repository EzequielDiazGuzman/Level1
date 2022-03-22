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
 * En este archvo se encuentra la declaracion de los metodos y datos
 * miembro de la clase que se utiliza para manejar la simulacion.
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
    float getRadius(int i);
    float getTimeStep();
    int getAsteroidsInSym();
    int getBodiesInSym();

    
    private:
    OrbitalBody *orbitalBodies;
    OrbitalBody *asteroids;
    int asteroidsInSym;
    int bodiesInSym;
    float timeStep;
    double timeElapsed;
};

#endif

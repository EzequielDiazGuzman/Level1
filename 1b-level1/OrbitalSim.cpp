/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include "OrbitalSim.hpp"
#include "ephemerides.h"
#include <stdlib.h>

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

// Make an orbital simulation
OrbitalSim::OrbitalSim(float timeStep)
{
    this->timeStep = timeStep;

    this->bodiesInSym = SOLARSYSTEM_BODYNUM;
    this->orbitalBodies = new OrbitalBody[this->bodiesInSym];

    this->asteroidsInSym = 1000;
    this->asteroids = new OrbitalBody[this->asteroidsInSym];
    
    for (int i=0; i<this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].initOrbitalBody(solarSystem[i].mass, solarSystem[i].radius, solarSystem[i].color, solarSystem[i].position, solarSystem[i].velocity);
    }

    for (int i=0; i<this->asteroidsInSym; i++)
    {
        // TODO: centermass no hardcodeado
        this->asteroids[i].initAsteroid(this->orbitalBodies[0].getMass());
    }

}

// Simulates a timestep
void OrbitalSim::updateOrbitalSim()
{
    this->updateAcceleration();
    this->updateVelocity();
    this->updatePosition();
}

OrbitalSim::~OrbitalSim()
{
    delete[] this->orbitalBodies;
    delete[] this->asteroids;
}


// position, velocity and acceleration calculating functions
void OrbitalSim::updatePosition ()
{
    for (int i = 0; i<this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].setPosition(Vector3Add(this->orbitalBodies[i].getPosition(), Vector3Scale(this->orbitalBodies[i].getVelocity(), this->timeStep)));
    }

    for (int i = 0; i<this->asteroidsInSym; i++)
    {
        this->asteroids[i].setPosition(Vector3Add(this->asteroids[i].getPosition(), Vector3Scale(this->asteroids[i].getVelocity(), this->timeStep)));
    }
}

void OrbitalSim::updateVelocity ()
{
    for (int i = 0; i<this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].setVelocity(Vector3Add(this->orbitalBodies[i].getVelocity(), Vector3Scale(this->orbitalBodies[i].getAcceleration(), this->timeStep)));
    }

    for (int i = 0; i<this->asteroidsInSym; i++)
    {
        this->asteroids[i].setVelocity(Vector3Add(this->asteroids[i].getVelocity(), Vector3Scale(this->asteroids[i].getAcceleration(), this->timeStep)));
    }
}

void OrbitalSim::updateAcceleration ()
{
    for (int i = 0; i < this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].setAcceleration(Vector3Zero());

        for (int j = 0; j < this->bodiesInSym; j++)
        {
            if (i != j)
            {
                float massj = this->orbitalBodies[j].getMass();
                Vector3 xij = Vector3Subtract(this->orbitalBodies[i].getPosition(), this->orbitalBodies[j].getPosition());
                this->orbitalBodies[i].setAcceleration(Vector3Add(this->orbitalBodies[i].getAcceleration(), Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3)))));
            }
        }
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
    {
        this->asteroids[i].setAcceleration(Vector3Zero());

        for (int j = 0; j < this->bodiesInSym; j++)
        {
            float massj = this->orbitalBodies[j].getMass();
            Vector3 xij = Vector3Subtract(this->asteroids[i].getPosition(), this->orbitalBodies[j].getPosition());
            this->asteroids[i].setAcceleration(Vector3Add(this->asteroids[i].getAcceleration(), Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3)))));
        }

        
    }
}

// Getters
float OrbitalSim::getTimeStep()
{
    return this->timeStep;
}

int OrbitalSim::getBodiesInSym()
{
    return this->bodiesInSym;
}

int OrbitalSim::getAsteroidsInSym()
{
    return this-> asteroidsInSym;
}

raylib::Vector3 OrbitalSim::getPosition(int i, bool asteroid)
{
    if (asteroid)
        return this->asteroids[i].getPosition();
    else
        return this->orbitalBodies[i].getPosition();
}

raylib::Color OrbitalSim::getColor(int i, bool asteroid)
{
    if (asteroid)
        return this->asteroids[i].getColor();
    else
        return this->orbitalBodies[i].getColor();
}

float OrbitalSim::getRadius(int i)
{
    return this->orbitalBodies[i].getRadius();
}
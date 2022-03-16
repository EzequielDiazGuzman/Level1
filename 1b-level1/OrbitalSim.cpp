/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include "OrbitalSim.hpp"
#include "ephemerides.h"
#include "OrbitalBody.hpp"
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
        this->asteroids[i].initAsteroid(this->orbitalBodies[0].mass);
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
        this->orbitalBodies[i].position = Vector3Add(this->orbitalBodies[i].position, Vector3Scale(this->orbitalBodies[i].velocity, this->timeStep));
    }

    for (int i = 0; i<this->asteroidsInSym; i++)
    {
        this->asteroids[i].position = Vector3Add(this->asteroids[i].position, Vector3Scale(this->asteroids[i].velocity, this->timeStep));
    }
}

void OrbitalSim::updateVelocity ()
{
    for (int i = 0; i<this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].velocity = Vector3Add(this->orbitalBodies[i].velocity, Vector3Scale(this->orbitalBodies[i].acceleration, this->timeStep));
    }

    for (int i = 0; i<this->asteroidsInSym; i++)
    {
        this->asteroids[i].velocity = Vector3Add(this->asteroids[i].velocity, Vector3Scale(this->asteroids[i].acceleration, this->timeStep));
    }
}

void OrbitalSim::updateAcceleration ()
{
    for (int i = 0; i < this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].acceleration = Vector3Zero();

        for (int j = 0; j < this->bodiesInSym; j++)
        {
            if (i != j)
            {
                float massj = this->orbitalBodies[j].mass;
                Vector3 xij = Vector3Subtract(this->orbitalBodies[i].position, this->orbitalBodies[j].position);
                this->orbitalBodies[i].acceleration = Vector3Add(this->orbitalBodies[i].acceleration, Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3))));
            }
        }
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
    {
        this->asteroids[i].acceleration = Vector3Zero();

        for (int j = 0; j < this->bodiesInSym; j++)
        {
            float massj = this->orbitalBodies[j].mass;
            Vector3 xij = Vector3Subtract(this->asteroids[i].position, this->orbitalBodies[j].position);
            this->asteroids[i].acceleration = Vector3Add(this->asteroids[i].acceleration, Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3))));
        }

        
    }
}
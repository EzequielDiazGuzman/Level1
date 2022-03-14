/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include "orbitalSim.h"
#include "ephemerides.h"
#include <stdlib.h>

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

void getAcceleration (OrbitalSim *sim);
void getVelocity (OrbitalSim *sim);
void getPosition (OrbitalSim *sim);

// Gets a random value between min and max
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

// Places an asteroid
//
// centerMass: mass of the most massive object in the star system
void placeAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabs(l));
    float phi = getRandomFloat(0, 2 * M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    body->radius = 2E3F; // Typical asteroid radius: 2km
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

// Make an orbital simulation
OrbitalSim *makeOrbitalSim(float timeStep)
{
    OrbitalSim * sim = (OrbitalSim*)malloc(sizeof(OrbitalSim));
    if (sim == NULL) return NULL;

    sim->timeStep = timeStep;
    sim->bodiesInSym = SOLARSYSTEM_BODYNUM;

    sim->orbitalBodies = (OrbitalBody*)malloc(sim->bodiesInSym*sizeof(OrbitalBody));
    if (sim->orbitalBodies == NULL) return NULL;

    sim->asteroidsInSym = 500;
    sim->asteroids = (OrbitalBody*)malloc(sim->asteroidsInSym*sizeof(OrbitalBody));

    for (int i=0; i<sim->asteroidsInSym; i++)
    {
        placeAsteroid(&(sim->asteroids[i]), sim->orbitalBodies[0].mass);
    }

    for (int i = 0; i < sim->bodiesInSym; i++)
    {
        sim->orbitalBodies[i].color = solarSystem[i].color;
        sim->orbitalBodies[i].mass = solarSystem[i].mass;
        sim->orbitalBodies[i].radius = solarSystem[i].radius;
        sim->orbitalBodies[i].position = solarSystem[i].position;
        sim->orbitalBodies[i].velocity = solarSystem[i].velocity;
        sim->orbitalBodies[i].acceleration = {0,0,0};
    };

    return sim;
}

// Simulates a timestep
void updateOrbitalSim(OrbitalSim *sim)
{
    getAcceleration(sim);
    getVelocity(sim);
    getPosition(sim);
}

void freeOrbitalSim(OrbitalSim *sim)
{
    free(sim->orbitalBodies);
    free(sim);
}


// position, velocity and acceleration calculating functions
void getPosition (OrbitalSim *sim)
{
    for (int i = 0; i<sim->bodiesInSym; i++)
    {
        sim->orbitalBodies[i].position = Vector3Add(sim->orbitalBodies[i].position, Vector3Scale(sim->orbitalBodies[i].velocity, sim->timeStep));
    }

    for (int i = 0; i<sim->asteroidsInSym; i++)
    {
        sim->asteroids[i].position = Vector3Add(sim->asteroids[i].position, Vector3Scale(sim->asteroids[i].velocity, sim->timeStep));
    }
}

void getVelocity (OrbitalSim *sim)
{
    for (int i = 0; i<sim->bodiesInSym; i++)
    {
        sim->orbitalBodies[i].velocity = Vector3Add(sim->orbitalBodies[i].velocity, Vector3Scale(sim->orbitalBodies[i].acceleration, sim->timeStep));
    }

    for (int i = 0; i<sim->asteroidsInSym; i++)
    {
        sim->asteroids[i].velocity = Vector3Add(sim->asteroids[i].velocity, Vector3Scale(sim->asteroids[i].acceleration, sim->timeStep));
    }
}

void getAcceleration (OrbitalSim *sim)
{
    for (int i = 0; i < sim->bodiesInSym; i++)
    {
        sim->orbitalBodies[i].acceleration = {0,0,0};

        for (int j = 0; j < sim->bodiesInSym; j++)
        {
            if (i != j)
            {
                float massj = sim->orbitalBodies[j].mass;
                Vector3 xij = Vector3Subtract(sim->orbitalBodies[i].position, sim->orbitalBodies[j].position);
                sim->orbitalBodies[i].acceleration = Vector3Add(sim->orbitalBodies[i].acceleration, Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3))));
            }
        }
    }

    for (int i = 0; i < sim->asteroidsInSym; i++)
    {
        sim->asteroids[i].acceleration = {0,0,0};

        for (int j = 0; j < sim->bodiesInSym; j++)
        {
            float massj = sim->orbitalBodies[j].mass;
            Vector3 xij = Vector3Subtract(sim->asteroids[i].position, sim->orbitalBodies[j].position);
            sim->asteroids[i].acceleration = Vector3Add(sim->asteroids[i].acceleration, Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3))));
        }

        for (int j = 0; j < sim->asteroidsInSym; j++)
        {
            if (i != j)
            {
                float massj = sim->asteroids[j].mass;
                Vector3 xij = Vector3Subtract(sim->asteroids[i].position, sim->asteroids[j].position);
                sim->asteroids[i].acceleration = Vector3Add(sim->asteroids[i].acceleration, Vector3Scale(xij, ((GRAVITATIONAL_CONSTANT*(-1)*massj))/(pow(Vector3Length(xij),3))));
            }
            
        }
    }
}
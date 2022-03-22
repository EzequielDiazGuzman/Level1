/*
 * Orbital Simulation
 *
 * 22.08 EDA
 * Level 1 - Warm Up
 *
 * Grupo 2
 * Autores: Diaz Guzman, Ezequiel & Fisher, Agustin
 * 
 * En este archvo se definen los metodos miembro de la clase OrbitalBody.
 */

#include "raylib-cpp.hpp"
#include "OrbitalBody.hpp"

OrbitalBody::OrbitalBody ()
{
    ;
}

OrbitalBody::~OrbitalBody()
{
    ;
}

void OrbitalBody::initOrbitalBody(float mass, float radius, raylib::Color color,
                                  raylib::Vector3 position, raylib::Vector3 velocity)
{
    this->mass = mass;
    this->radius = radius;
    this->color = color;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = Vector3Zero();
}


// Gets a random value between min and max
float OrbitalBody::getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

void OrbitalBody::initAsteroid(float centermass)
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
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centermass / r) * 
              getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    this->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    this->radius = 5E2F; // Typical asteroid radius: 2km
    this->color = GRAY;
    this->position = raylib::Vector3(r * cosf(phi), 0, r * sinf(phi));
    this->velocity = raylib::Vector3(-v * sinf(phi), vy, v * cosf(phi));
}

// Getters
raylib::Vector3 OrbitalBody::getPosition()
{
    return this->position;
}

raylib::Vector3 OrbitalBody::getVelocity()
{
    return this->velocity;
}

raylib::Vector3 OrbitalBody::getAcceleration()
{
    return this->acceleration;
}

raylib::Color OrbitalBody::getColor()
{
    return this->color;
}

float OrbitalBody::getRadius()
{
    return this->radius;
}

float OrbitalBody::getMass()
{
    return this->mass;
}

// Setters
void OrbitalBody::setPosition(raylib::Vector3 x)
{
    this->position = x;
}

void OrbitalBody::setVelocity(raylib::Vector3 x)
{
    this->velocity = x;
}

void OrbitalBody::setAcceleration(raylib::Vector3 x)
{
   this->acceleration = x;
}
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
 * miembro de la clase que se utiliza para manejar cada cuerpo celeste.
 */

#ifndef ORBITALBODY_H
#define ORBITALBODY_H

#include "raylib-cpp.hpp"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

class OrbitalBody
{
    public:
    OrbitalBody();
    ~OrbitalBody();

    void initOrbitalBody(float mass, float radius, raylib::Color color, 
                         raylib::Vector3 position, raylib::Vector3 velocity);
    void initAsteroid(float centermass);

    raylib::Vector3 getPosition();
    raylib::Vector3 getVelocity();
    raylib::Vector3 getAcceleration();
    void setPosition(raylib::Vector3 x);
    void setVelocity(raylib::Vector3 x);
    void setAcceleration(raylib::Vector3 x);

    raylib::Color getColor();
    float getRadius();
    float getMass();

    
    private:
    float getRandomFloat(float min, float max);
    float mass;
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;
    raylib::Color color;
    float radius;
};

#endif
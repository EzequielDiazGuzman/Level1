#include "raylib-cpp.hpp"
#include "orbitalBody.h"

orbitalBody::orbitalBody(float mass, float radius, raylib::Color color, raylib::Vector3 position, raylib::Vector3 velocity)
{
    this->mass = mass;
    this->radius = radius;
    this->color = color;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = Vector3Zero();
}

raylib::Vector3 orbitalBody::getPosition()
{
    return this->position;
}
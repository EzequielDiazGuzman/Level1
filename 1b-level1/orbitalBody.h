#include "raylib-cpp.hpp"

class orbitalBody
{
    public:
    orbitalBody();
    ~orbitalBody();

    orbitalBody(float mass, float radius, raylib::Color color, raylib::Vector3 position, raylib::Vector3 velocity);

    raylib::Vector3 getPosition();

    private:
    float mass;
    float radius;
    raylib::Color color;
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;

    raylib::Vector3 getVelocity();
    raylib::Vector3 updatePosition();
    raylib::Vector3 updateVelocity();
    raylib::Vector3 updateAcceleration();
};
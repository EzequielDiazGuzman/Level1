#include "raylib-cpp.hpp"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

class OrbitalBody
{
    public:
    OrbitalBody();
    ~OrbitalBody();

    void initOrbitalBody(float mass, float radius, raylib::Color color, raylib::Vector3 position, raylib::Vector3 velocity);
    void initAsteroid(float centermass);

    raylib::Vector3 getPosition();

    float mass;
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;
    raylib::Color color;
    float radius;
    
    private:
    float getRandomFloat(float min, float max);
    raylib::Vector3 getVelocity();
};
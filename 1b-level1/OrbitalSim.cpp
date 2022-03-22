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
 * En este archivo se definen los metodos utilizados para crear, actualizar y
 * destruir la simulacion.
 */

/* PRECISION DE FLOAT
 * El float usa 32 bits para representar numeros decimales no enteros en el
 * fomato IEEE 754. En terminos de decimales se puede decir que tiene una precision
 * de 7 digitos despues de la coma o 10^-7. Para magnitudes del orden en el que se
 * trabaja en esta simulacion (masas de planetas, millones de kilometros) y
 * para los fines de la misma, esta precision resulta ser suficiente.
 * 
 * Por ejemplo, al ingresar el numero -1.283674643550172E+09F (este es el valor
 * de la coordenada en x de la posicion inicial del sol), se representa como
 * -1.283674624E+09F. El error es de 1.52E-8. Esto es suficiente precision para
 * nuestra simulacion.
 *
 * CUELLOS DE BOTELLA
 * Un cuello de botella importante surge de dibujar los asteroides como esferas.
 * Las esferas se dibujan como muchos triangulos pequenos, para aproximar la forma
 * de una esfera, esto es muy costoso en operaciones y, hacerlo para todos los 
 * asteroides, hace disminuir notablemente los FPS. Lo resolvimos dibujando los 
 * asteroides como puntos, ya que se pueden apreciar igual de bien y aumenta 
 * drasticamente el rendimiento de la simulacion. 
 * 
 * El otro cuello de botella es de complejidad y nace de los calculos de las
 * fuerzas para los asteroides. Inicialmente, el programa calculaba las fuerzas
 * de interaccion de los planetas entre ellos y con el sol. Con los asteroides,
 * calculando la fuerza de cada par asteroide-asteroide, planeta-asteroide, 
 * planeta-planeta, planeta-sol y asteroide-sol, es demasiado. Ademas, la fuerza 
 * de atraccion entre dos asteroides es casi despresiable comparada a la de esos
 * asteroides con el sol y con otros planetas. Por lo tanto, dejando de lado la
 * interaccion entre asteroides se obtiene una simulacion lo suficientemente precisa
 * y vastamente superior en rendimiento
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
    
    for (int i = 0; i < this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].initOrbitalBody(solarSystem[i].mass, solarSystem[i]
                                               .radius, solarSystem[i].color,
                                               solarSystem[i].position, solarSystem[i]
                                               .velocity);
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
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
    for (int i = 0; i < this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].setPosition(Vector3Add(this->orbitalBodies[i].
                                           getPosition(), Vector3Scale(this->
                                           orbitalBodies[i].getVelocity(), this->
                                           timeStep)));
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
    {
        this->asteroids[i].setPosition(Vector3Add(this->asteroids[i].getPosition(),
                                       Vector3Scale(this->asteroids[i].getVelocity(),
                                       this->timeStep)));
    }
}

void OrbitalSim::updateVelocity ()
{
    for (int i = 0; i < this->bodiesInSym; i++)
    {
        this->orbitalBodies[i].setVelocity(Vector3Add(this->orbitalBodies[i].
                                           getVelocity(), Vector3Scale(this->
                                           orbitalBodies[i].getAcceleration(),
                                           this->timeStep)));
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
    {
        this->asteroids[i].setVelocity(Vector3Add(this->asteroids[i].getVelocity(),
                                       Vector3Scale(this->asteroids[i].
                                       getAcceleration(), this->timeStep)));
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
                Vector3 xij = Vector3Subtract(this->orbitalBodies[i].getPosition(),
                                              this->orbitalBodies[j].getPosition());
                this->orbitalBodies[i].setAcceleration(Vector3Add(this->orbitalBodies[i].
                                                       getAcceleration(), Vector3Scale(
                                                       xij,((GRAVITATIONAL_CONSTANT*(-1)
                                                       *massj))/(pow(Vector3Length(xij),3)))));
            }
        }
    }

    for (int i = 0; i < this->asteroidsInSym; i++)
    {
        this->asteroids[i].setAcceleration(Vector3Zero());

        for (int j = 0; j < this->bodiesInSym; j++)
        {
            float massj = this->orbitalBodies[j].getMass();
            Vector3 xij = Vector3Subtract(this->asteroids[i].getPosition(),
                                          this->orbitalBodies[j].getPosition());
            this->asteroids[i].setAcceleration(Vector3Add(this->asteroids[i].
                                               getAcceleration(), Vector3Scale(xij,
                                               ((GRAVITATIONAL_CONSTANT*(-1)
                                               *massj))/(pow(Vector3Length(xij),3)))));
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
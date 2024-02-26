#include "movementalgorithm.h"

const double MovementAlgorithm::G  = 6.679;

MovementAlgorithm::MovementAlgorithm()
{

}

MovementAlgorithm::~MovementAlgorithm()
{

}

void MovementAlgorithm::eulersMethod(std::vector<Body*> &bodies)
{
    for(int i = 0 ; i < bodies.size(); ++i)
    {
        bodies[i]->set_acceleration(getAcceleration(bodies, bodies[i]->get_position(), i));
        bodies[i]->set_velocity(bodies[i]->get_velocity() + bodies[i]->get_acceleration());
    }
    for(auto&& a : bodies)
        a->set_position(a->get_position() + a->get_velocity());
}

void MovementAlgorithm::rungeKutta4(std::vector<Body *> &bodies)
{
    FreeVector currentPosition;
    FreeVector acceleration;
    FreeVector velocity;
    FreeVector position;

    FreeVector kv1, kv2, kv3, kv4; // for velocity
    FreeVector kp1, kp2, kp3, kp4; // for position
    std::vector<FreeVector> newPositions;
    newPositions.reserve(bodies.size());
    for(int i = 0 ; i < bodies.size(); ++i)
    {
        currentPosition = bodies[i]->get_position();
        acceleration = getAcceleration(bodies, bodies[i]->get_position(), i);
        velocity = bodies[i]->get_velocity();

        kp1 = velocity;
        kv1 = acceleration;

        kp2 = velocity * kv1 / 2;
        kv2 = getAcceleration(bodies, currentPosition + kp1 /2, i);

        kp3 = velocity * kv2 / 2;
        kv3 = getAcceleration(bodies, currentPosition + kp2 / 2, i);

        kp4 = velocity * kv3;
        kv4 = getAcceleration(bodies, currentPosition + kp3, i);

        velocity = velocity + acceleration + (kv1 + kv2 * 2 + kv3 * 2 + kv4) / 6;
        currentPosition = currentPosition + velocity + (kp1 + kp2 * 2 + kp3 * 2 + kp4) / 6;

        bodies[i]->set_acceleration(acceleration);
        bodies[i]->set_velocity(velocity);
        newPositions.emplace_back(currentPosition);
    }
    for(int i = 0; i < bodies.size(); ++i)
        bodies[i]->set_position(newPositions[i]);

}

const FreeVector MovementAlgorithm::getAcceleration(const std::vector<Body *>& bodies, const FreeVector& position, const int idx)
{
    FreeVector acceleration = {0, 0};
    FreeVector distance; // distance vector
    qreal dl; // distance vector lenght

    for(int j = 0; j < bodies.size(); ++j)
        if(idx != j)
        {
            distance = bodies[j]->get_position() - position;
            dl = distance.getLength();
            distance = distance / dl; // normalization
            acceleration = acceleration + (distance * (G * bodies[j]->get_mass() / (dl * dl)));
        }
    if(qAbs(acceleration.getX()) < 0.00001 && qAbs(acceleration.getY()) < 0.00001)
        acceleration = {0,0};
    return acceleration;
}

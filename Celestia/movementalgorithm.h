#ifndef MOVEMENTALGORITHM_H
#define MOVEMENTALGORITHM_H
#include "body.h"

class MovementAlgorithm
{
public:
    MovementAlgorithm();
    ~MovementAlgorithm();

    static void eulersMethod(std::vector<Body*>& bodies);
    static void rungeKutta4(std::vector<Body*>& bodies);
private:
    static const FreeVector getAcceleration(const std::vector<Body*>& bodies, const FreeVector& position, const int idx);
    static const double G;
};

#endif // MOVEMENTALGORITHM_H

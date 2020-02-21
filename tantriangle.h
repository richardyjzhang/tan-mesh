#ifndef TANTRIANGLE_H
#define TANTRIANGLE_H

#include "tannode.h"

class TanTriangle
{
public:
    TanTriangle();
    TanTriangle(long idA, long idB, long idC);

private:
    long idA;
    long idB;
    long idC;

public:
    bool valid() const;
};

#endif // TANTRIANGLE_H

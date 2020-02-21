#include "tantriangle.h"

TanTriangle::TanTriangle()
    : idA(0), idB(0), idC(0) { }

TanTriangle::TanTriangle(long idA, long idB, long idC)
    : idA(idA), idB(idB), idC(idC) { }

bool TanTriangle::valid() const
{
    if (idA <= 0 || idB <= 0 || idC <= 0) return false;
    if (idA == idB || idA == idC || idB == idC) return false;

    TanNode nodeA = TanNode::getNodeById(idA);
    TanNode nodeB = TanNode::getNodeById(idB);
    TanNode nodeC = TanNode::getNodeById(idC);

    return nodeA.valid() && nodeB.valid() && nodeC.valid();
}

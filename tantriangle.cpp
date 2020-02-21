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

long TanTriangle::getIdA() const { return idA; }

long TanTriangle::getIdB() const { return idB; }

long TanTriangle::getIdC() const { return idC; }

void TanTriangle::turn()
{
    std::swap(idA, idC);
}

TanVector TanTriangle::getNormal() const
{
    TanVector vec(0, 0, 1);
    if (!valid()) return vec;

    TanNode nodeA = TanNode::getNodeById(idA);
    TanNode nodeB = TanNode::getNodeById(idB);
    TanNode nodeC = TanNode::getNodeById(idC);

    TanVector vecAB = (nodeB.getVector() - nodeA.getVector()).normalize();
    TanVector vecBC = (nodeC.getVector() - nodeB.getVector()).normalize();
    vec = TanVector::crossProduct(vecAB, vecBC).normalize();

    return vec;
}

double TanTriangle::getMaxEdge(long & idS, long & idE, long & idAngle) const
{
    if (!valid()) return 0.0;

    TanNode nodeA = TanNode::getNodeById(idA);
    TanNode nodeB = TanNode::getNodeById(idB);
    TanNode nodeC = TanNode::getNodeById(idC);

    TanVector vecAB = nodeB.getVector() - nodeA.getVector();
    TanVector vecBC = nodeC.getVector() - nodeB.getVector();
    TanVector vecCA = nodeA.getVector() - nodeC.getVector();
    double ab = vecAB.length();
    double bc = vecBC.length();
    double ca = vecCA.length();

    double maxLen = 0.0;
    if (ab >= bc && ab >= ca)
    {
        idS = idA;
        idE = idB;
        idAngle = idC;
        maxLen = ab;
    }
    else if (bc >= ab && bc >= ca)
    {
        idS = idB;
        idE = idC;
        idAngle = idA;
        maxLen = bc;
    }
    else
    {
        idS = idC;
        idE = idA;
        idAngle = idB;
        maxLen = ca;
    }
    return maxLen;
}

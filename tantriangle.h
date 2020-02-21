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
    long getIdA() const;
    long getIdB() const;
    long getIdC() const;

    // 翻转顺序，将ABC翻转为CBA，以调整法向
    void turn();

    // 获取按ABC顺序给出的三角形法向
    TanVector getNormal() const;

    // 获取三角形的最长边，返回长度，并给出Start End和Angle三个点
    double getMaxEdge(long & idS, long & idE, long & idAngle) const;
};

#endif // TANTRIANGLE_H

#ifndef TANMESHTOOL_H
#define TANMESHTOOL_H

#include <QString>
#include <vector>
#include "tantriangle.h"

class TanMeshTool
{
public:
    TanMeshTool(const QString & input, const QString & output, double tolerance, double maxLen);

private:
    QString input;
    QString output;
    double tolerance;
    double maxLen;

public:
    bool mesh();

private:
    void meshOneTriangle(const TanTriangle & triangle, std::vector<TanTriangle> & triangles);
};

#endif // TANMESHTOOL_H

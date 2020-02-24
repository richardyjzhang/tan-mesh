#ifndef TANMESHTOOLBASIC_H
#define TANMESHTOOLBASIC_H

#include <QString>
#include <vector>
#include "tanmeshtool.h"

class TanMeshToolBasic : public TanMeshTool
{
public:
    TanMeshToolBasic(const QString & input, const QString & output, double tolerance, double maxLen);
    virtual ~TanMeshToolBasic();

public:
    virtual bool mesh();

private:
    void meshOneTriangle(const TanTriangle & triangle, std::vector<TanTriangle> & triangles);
};

#endif // TANMESHTOOL_H

#ifndef TANMESHTOOL_H
#define TANMESHTOOL_H

#include <QString>
#include "tantriangle.h"

// 各种分割方式的虚基类
class TanMeshTool
{
public:
    TanMeshTool(const QString & input, const QString & output, double tolerance, double maxLen);
    virtual ~TanMeshTool();

protected:
    QString input;
    QString output;
    double tolerance;
    double maxLen;

public:
    virtual bool mesh() = 0;
};

#endif // TANMESHTOOL_H

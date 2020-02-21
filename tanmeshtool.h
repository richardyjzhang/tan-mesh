#ifndef TANMESHTOOL_H
#define TANMESHTOOL_H

#include <QString>

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
};

#endif // TANMESHTOOL_H

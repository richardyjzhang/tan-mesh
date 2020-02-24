#ifndef TANMESHTOOLEQUALLY_H
#define TANMESHTOOLEQUALLY_H

#include "tanmeshtool.h"

class TanMeshToolEqually : public TanMeshTool
{
public:
    TanMeshToolEqually(const QString & input, const QString & output, double tolerance, double maxLen);
    virtual ~TanMeshToolEqually() override;

public:
    virtual bool mesh() override;

private:
    int calcMaxDivision(const std::vector<TanTriangle> & triangles);
    void calcOneLineVectors(int cnt, int i, TanTriangle triangle,
                            std::map<int, std::vector<TanVector>> & mapLine2Vectors);
    void meshOneTriangle(int cnt, const TanTriangle & triangle, std::vector<TanTriangle> & triangles);
};

#endif // TANMESHTOOLEQUALLY_H

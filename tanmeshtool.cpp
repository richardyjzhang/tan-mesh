#include "tanmeshtool.h"
#include "inpoperator.h"
#include <vector>
#include "tantriangle.h"

TanMeshTool::TanMeshTool(const QString & input, const QString & output, double tolerance, double maxLen)
    : input(input), output(output), tolerance(tolerance), maxLen(maxLen) { }

bool TanMeshTool::mesh()
{
    TanVector::setTolerance(tolerance);
    std::vector<TanTriangle> triangles;
    bool success = InpOperator::ReadInpFile(input, triangles);
    return success;
}

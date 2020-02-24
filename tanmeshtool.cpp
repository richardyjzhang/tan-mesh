#include "tanmeshtool.h"

TanMeshTool::TanMeshTool(const QString & input, const QString & output, double tolerance, double maxLen)
    : input(input), output(output), tolerance(tolerance), maxLen(maxLen) { }

TanMeshTool::~TanMeshTool() { }

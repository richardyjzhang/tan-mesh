#include "tanmeshtool.h"
#include "inpoperator.h"
#include <vector>
#include "tantriangle.h"

TanMeshTool::TanMeshTool(const QString & input, const QString & output, double tolerance, double maxLen)
    : input(input), output(output), tolerance(tolerance), maxLen(maxLen) { }

bool TanMeshTool::mesh()
{
    TanVector::setTolerance(tolerance);
    std::vector<TanTriangle> oriTriangles;
    bool success = InpOperator::ReadInpFile(input, oriTriangles);

    std::vector<TanTriangle> triangles;
    for (auto it = oriTriangles.begin(); it != oriTriangles.end(); ++it)
        meshOneTriangle(*it, triangles);

    return success;
}

/**
 * 剖分一个三角形
 * 思路，根据所限定的maxLen，可以唯一的确定一个边应该被剖分成几份
 * 因此一个被公用的长边在被引用的三角形中会被一致地分割
 * 如果三边均小于maxLen，则不用分割，可直接加入结果列表；
 * 否则以最长边进行分割，并将得到的小三角形再次调用本函数，直至成功
 */
void TanMeshTool::meshOneTriangle(const TanTriangle & triangle, std::vector<TanTriangle> & triangles)
{
    long idS, idE, idAngle;
    double curMax = triangle.getMaxEdge(idS, idE, idAngle);
    if (curMax <= maxLen)
    {
        // 如果最长边都满足要求，说明可以放在结果列表中结束了
        triangles.push_back(triangle);
        return;
    }

    // 需要将最长边划分为几段，就是新生成几个新的小三角形，再分别调用本函数
    int cnt = int(curMax / maxLen) + 1;
    TanNode nodeS = TanNode::getNodeById(idS);
    TanNode nodeE = TanNode::getNodeById(idE);
    TanNode nodeA = TanNode::getNodeById(idAngle);
    TanVector vecSE = (nodeE.getVector() - nodeS.getVector()).normalize();
    TanVector vecNormal = triangle.getNormal();

    for (int i = 0; i < cnt; ++i)
    {
        TanVector vecNewB = nodeS.getVector() + curMax / cnt * i * vecSE;
        TanVector vecNewC = vecNewB + curMax / cnt * vecSE;
        TanNode nodeNewB = TanNode::getNodeByVector(vecNewB);
        TanNode nodeNewC = TanNode::getNodeByVector(vecNewC);
        TanTriangle newTriangle(nodeNewB.getId(), nodeNewC.getId(), nodeA.getId());

        // 这里进行处理，保证新生成的小三角形和原始三角形法向一致
        if (TanVector::opposite(vecNormal, newTriangle.getNormal())) newTriangle.turn();
        meshOneTriangle(newTriangle, triangles);
    }
}

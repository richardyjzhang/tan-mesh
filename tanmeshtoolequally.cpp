#include "tanmeshtoolequally.h"
#include "inpoperator.h"

TanMeshToolEqually::TanMeshToolEqually(const QString & input, const QString & output, double tolerance, double maxLen)
    : TanMeshTool(input, output, tolerance, maxLen) { }

TanMeshToolEqually::~TanMeshToolEqually() { }

bool TanMeshToolEqually::mesh()
{
    TanVector::setTolerance(tolerance);
    std::vector<TanTriangle> oriTriangles;
    bool success = InpOperator::ReadInpFile(input, oriTriangles);

    // 所有输入三角形的边被按照一致的份数被均等分割，这里根据最长边计算出应被分割的份数
    if (oriTriangles.size() <= 0) success = false;
    int maxDivision = calcMaxDivision(oriTriangles);
    std::vector<TanTriangle> triangles;
    if (success)
    {
        for (auto it = oriTriangles.begin(); it != oriTriangles.end(); ++it)
            meshOneTriangle(maxDivision, *it, triangles);
    }

    success = success && InpOperator::WriteInpFile(output, triangles);
    TanNode::clearAllNodes();

    return success;
}

int TanMeshToolEqually::calcMaxDivision(const std::vector<TanTriangle> & triangles)
{
    double maxEdge = 0.0;
    for (auto it = triangles.begin(); it != triangles.end(); ++it)
    {
        double curMaxEdge = it->getMaxEdge();
        if (curMaxEdge > maxEdge) maxEdge = curMaxEdge;
    }

    if (maxEdge < tolerance) return 1;
    return int(maxEdge / maxLen) + 1;
}

void TanMeshToolEqually::calcOneLineVectors(int cnt, int i, TanTriangle triangle,
                                            std::map<int, std::vector<TanVector>> & mapLine2Vectors)
{
    // 工具函数，计算分割时第i行的点列表
    if (cnt <= 1 || i < 0 || i > cnt) return;
    if (!triangle.valid()) return;

    long idA = triangle.getIdA();
    long idB = triangle.getIdB();
    long idC = triangle.getIdC();
    TanVector A = TanNode::getNodeById(idA).getVector();
    TanVector B = TanNode::getNodeById(idB).getVector();
    TanVector C = TanNode::getNodeById(idC).getVector();
    TanVector AB = (B - A).normalize();
    TanVector BC = (C - B).normalize();
    double ab = AB.length();
    double bc = BC.length();

    std::vector<TanVector> vecs;
    for (int j = 0; j <= i; ++j)
    {
        TanVector vec = A + ab * i / cnt * AB + bc * j / cnt * BC;
        vecs.push_back(vec);
    }
    mapLine2Vectors[i] = vecs;
}

void TanMeshToolEqually::meshOneTriangle(int cnt, const TanTriangle & triangle, std::vector<TanTriangle> & triangles)
{
    if (!triangle.valid()) return;

    // 用于存储各行的点，第i行会有i+1个点
    std::map<int, std::vector<TanVector>> mapLine2Vectors;

    // cnt等分时，共需处理cnt+1行
    for (int i = 0; i<= cnt; ++i)
    {
        // 首先计算该行所有点
        calcOneLineVectors(cnt, i, triangle, mapLine2Vectors);

        // 不处理首行
        if (0 == i) continue;

        // 除首行外，每行处理i个点
        for (int j = 0; j < i; ++j)
        {
            // 以ij为下角的三角形，每行第0个点没有
            if (0 != j)
            {
                TanVector upLeft = mapLine2Vectors[i - 1][j - 1];
                TanVector down = mapLine2Vectors[j][j];
                TanVector upRight = mapLine2Vectors[i - 1][j];
                long id1 = TanNode::getNodeByVector(upLeft, true).getId();
                long id2 = TanNode::getNodeByVector(down, true).getId();
                long id3 = TanNode::getNodeByVector(upRight, true).getId();
                TanTriangle newTriangle(id1, id2, id3);
                triangles.push_back(newTriangle);
            }

            // 以ij为左下角点三角形，范围内各ij点均有
            {
                TanVector up = mapLine2Vectors[i - 1][j];
                TanVector downLeft = mapLine2Vectors[i][j];
                TanVector downRight = mapLine2Vectors[i][j + 1];
                long id1 = TanNode::getNodeByVector(up, true).getId();
                long id2 = TanNode::getNodeByVector(downLeft, true).getId();
                long id3 = TanNode::getNodeByVector(downRight, true).getId();
                TanTriangle newTriangle(id1, id2, id3);
                triangles.push_back(newTriangle);
            }
        }
    }
}

#include "inpoperator.h"
#include <QTextStream>
#include <QFile>

/**
 * 读入Inp文件
 * 约定以**开头的为注释，忽略不读
 * 约定读取*NODE开头的节点区域和*ELEMENT开头的单元区域
 * 约定先出现节点区域，再出现单元区域
 * 约定节点区域每行包括逗号分割的编号，xyz坐标值
 * 约定单元区域每行包括逗号分割的编号，三个节点编号值
 * 约定单元中三个节点顺序构成该单元法向
 */
bool InpOperator::ReadInpFile(const QString & input, std::vector<TanTriangle> & triangles)
{
    QFile file(input);
    if (!file.exists()) return false;

    if (!file.open(QIODevice::ReadOnly)) return false;
    QTextStream txt(&file);
    QString line;
    bool element = false; // 是否开始处理element区段
    bool success = true;
    std::map<long, long> mapIdOld2New;
    while (!txt.atEnd())
    {
        line = txt.readLine().trimmed();

        // *开头行的处理
        if (line.startsWith("*ELEMENT")) element = true;
        if (line.startsWith("*")) continue;

        if (!element) success = success && ReadOneNode(line, mapIdOld2New);
        else success = success && ReadOneElement(line, mapIdOld2New, triangles);
    }
    return success;
}

bool InpOperator::ReadOneNode(const QString & line,
                              std::map<long, long> & mapIdOld2New)
{
    QStringList lst = line.split(",");
    if (4 != lst.size()) return false;

    bool okId, okX, okY, okZ;
    long idOld = lst[0].trimmed().toLong(&okId);
    double x = lst[1].trimmed().toDouble(&okX);
    double y = lst[2].trimmed().toDouble(&okY);
    double z = lst[3].trimmed().toDouble(&okZ);
    if (!(okId && okX && okY && okZ)) return false;

    TanNode node = TanNode::getNodeByVector(TanVector{x, y, z}, true);
    mapIdOld2New[idOld] = node.getId();
    return true;
}

bool InpOperator::ReadOneElement(const QString & line,
                                 const std::map<long, long> & mapIdOld2New,
                                 std::vector<TanTriangle> & triangles)
{
    QStringList lst = line.split(",");
    if (4 != lst.size()) return false;

    bool ok1, ok2, ok3;
    long id1 = lst[1].trimmed().toLong(&ok1);
    long id2 = lst[2].trimmed().toLong(&ok2);
    long id3 = lst[3].trimmed().toLong(&ok3);
    if (!(ok1 && ok2 && ok3)) return false;

    auto it1 = mapIdOld2New.find(id1);
    auto it2 = mapIdOld2New.find(id2);
    auto it3 = mapIdOld2New.find(id3);
    auto itEnd = mapIdOld2New.end();
    if (it1 == itEnd || it2 == itEnd || it3 == itEnd) return false;

    TanTriangle triangle(it1->second, it2->second, it3->second);
    bool valid = triangle.valid();

    if (valid) triangles.push_back(triangle);

    return valid;
}

bool InpOperator::WriteInpFile(const QString & output)
{
    return true;
}

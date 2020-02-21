#ifndef INPOPERATOR_H
#define INPOPERATOR_H

#include <QString>
#include <QTextStream>
#include <map>
#include <vector>
#include "tantriangle.h"

class InpOperator
{
public:
    static bool ReadInpFile(const QString & input, std::vector<TanTriangle> & triangles);
    static bool WriteInpFile(const QString & output, const std::vector<TanTriangle> & triangles);

private:
    static bool ReadOneNode(const QString & line, std::map<long, long> & mapIdOld2New);
    static bool ReadOneElement(const QString & line,
                               const std::map<long, long> & mapIdOld2New,
                               std::vector<TanTriangle> & triangles);
    static void WriteHeader(QTextStream & txt);
    static void WriteFooter(QTextStream & txt);
    static void WriteNodes(QTextStream & txt);
    static void WriteElements(QTextStream & txt, const std::vector<TanTriangle> & triangles);
};

#endif // INPOPERATOR_H

#ifndef TANNODE_H
#define TANNODE_H

#include <map>
#include "tanvector.h"

class TanNode
{
public:
    TanNode();
    TanNode(const TanVector & vec);
    TanNode(double x, double y, double z);

private:
    TanVector vec;
    long id;
    static long curId;
    static std::map<TanNode, long> mapNode2Id;
    static std::map<long, TanNode> mapId2Node;

public:
    bool valid() const;
    long getId() const;
    TanVector getVector() const;

public:
    static TanNode getNodeById(long id);
    static TanNode getNodeByVector(const TanVector & vector, bool create = false);
    friend bool operator < (const TanNode & n1, const TanNode & n2);
};

bool operator < (const TanNode & n1, const TanNode & n2);

#endif // TANNODE_H

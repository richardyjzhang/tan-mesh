#include "tannode.h"

long TanNode::curId = 0;
std::map<long, TanNode> TanNode::mapId2Node;
std::map<TanNode, long> TanNode::mapNode2Id;

TanNode::TanNode()
    : vec(), id(0) { }

TanNode::TanNode(const TanVector & vec)
    : vec(vec), id(0) { }

TanNode::TanNode(double x, double y, double z)
    : vec(x, y, z), id(0) { }

bool TanNode::valid() const { return id > 0; }

long TanNode::getId() const { return id; }

TanVector TanNode::getVector() const { return vec; }

std::map<long, TanNode> TanNode::getAllNodes()
{
    return mapId2Node;
}

void TanNode::clearAllNodes()
{
    mapId2Node.clear();
    mapNode2Id.clear();
}

TanNode TanNode::getNodeById(long id)
{
    auto it = mapId2Node.find(id);
    if (it != mapId2Node.end()) return it->second;
    return TanNode();
}

TanNode TanNode::getNodeByVector(const TanVector & vector, bool create)
{
    TanNode node(vector);
    auto it = mapNode2Id.find(node);
    if (it != mapNode2Id.end()) return it->first;
    if (create)
    {
        node.id = ++curId;
        mapNode2Id[node] = node.id;
        mapId2Node[node.id] = node;
    }
    return node;
}

bool operator < (const TanNode & n1, const TanNode & n2)
{
    return n1.vec < n2.vec;
}

#include <iostream>
#include <set>

class Node;
using NodePair = std::pair<Node, int>;

class Node
{

public:
    Node()
    {
    }
    Node(int _x, int _y, int _z, float _val) : x(_x), y(_y), z(_z), value(_val)
    {
    }

    int x, y, z;
    float value;

    friend inline std::ostream &operator<<(std::ostream &os, const Node &dt)
    {
        os << "[" << dt.x << ", " << dt.y << ", " << dt.z << "], [" << dt.value << "]";
        return os;
    }
};


struct NodeComparator
{

    bool operator()(const NodePair &lhs__, const NodePair &rhs__) const
    {
        const Node lhs = lhs__.first;
        const Node rhs = rhs__.first;
        if( lhs.x == rhs.x && 
            lhs.y == rhs.y &&
            lhs.z == rhs.z ){
                // std::cout << "Found same node" << std::endl;
                return false;
        }

        float res = 0;
        res = lhs.value - rhs.value;

        if (res == 0)
        {
            res = lhs.x - rhs.x;
        }
        if (res == 0)
        {
            res = lhs.y - rhs.y;
        }
        if (res == 0)
        {
            res = lhs.z - rhs.z;
        }
        
        return res < 0;
    }
};
int main(int argc, char **argv)
{
    
    Node n1(0, 2, 4, 1.5), n2(2, 4, 5, 2.5), n3(0, 1, 4, 3.4), n4(0, 1, 4, 2.0), n5(0, 1, 5, 2.0);
    Node n6(0,2,4,1.0);
    std::cout << "Node 1: " << n1 << std::endl;
    std::cout << "Node 2: " << n2 << std::endl;
    std::cout << "Node 3: " << n3 << std::endl;
    std::cout << "Node 4: " << n4 << std::endl;
    std::cout << "Node 5: " << n5 << std::endl;
    std::cout << "Node 6: " << n6 
              << std::endl;

    std::set<NodePair, NodeComparator> set;
    set.insert({n1, n1.value});
    set.insert({n2, n2.value});
    set.insert({n3, n3.value});
    set.insert({n4, n4.value});
    set.insert({n5, n5.value});
    
    //Try to insert multiple times a previously inserted node (n1 is == n6)
    set.insert({n6, n6.value});
    set.insert({n6, n6.value});
    set.insert({n6, n6.value});
    set.insert({n6, n6.value});
    set.insert({n6, 0});
    set.insert({n6, 1});

    if(set.find({n4, n4.value}) != set.end()){
        std::cout << "Found n4" << std::endl;
    }

    auto it = set.erase({n4,4});
    std::cout << "It value: " << it << std::endl;
    if(set.find({n4, n4.value}) != set.end()){
        std::cout << "Found n4 after removal" << std::endl;

    }
    for (auto &it : set)
    {
        std::cout << it.first << std::endl;
    }
    return 0;
}
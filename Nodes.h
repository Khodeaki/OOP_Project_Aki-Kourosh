#ifndef NODES_H
#define NODES_H

#include <string>
#include <vector>
#include <algorithm>

class Nodes {
private:
    std::string nodeName;
    double nodeVoltage;
    std::vector<std::string> connectedNodes;
    bool isGround;

public:
    Nodes();
    Nodes(std::string name, double v = 0.0);

    void changeNodeName(std::string newName);
    std::string getNodeName();

    void addConnectedNode(std::string name);
    void removeConnectedNod(std::string name);

    void setGround();
};

#endif // NODES_H

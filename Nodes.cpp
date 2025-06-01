#include "Nodes.h"

Nodes::Nodes() : nodeName(""), nodeVoltage(0.0), isGround(false) {}

Nodes::Nodes(std::string name, double v) : nodeName(name), nodeVoltage(v), isGround(false) {}

void Nodes::changeNodeName(std::string newName) {
    nodeName = newName;
}

std::string Nodes::getNodeName() {
    return nodeName;
}

void Nodes::addConnectedNode(std::string name) {
    connectedNodes.push_back(name);
}

void Nodes::removeConnectedNod(std::string name) {
    connectedNodes.erase(
            std::remove(connectedNodes.begin(), connectedNodes.end(), name),
            connectedNodes.end()
    );
}

void Nodes::setGround() {
    isGround = true;
}

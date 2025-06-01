#include "view.h" // Include the header file for the view class
#include <iostream> // For std::cerr and std::cout
#include <algorithm> // For std::remove
#include <map>
#include <vector>
#include <string>

// Include headers for other classes used by view (e.g., Nodes, Resistor, Capacitor, etc.)
// These are placeholders; replace them with the actual paths to your header files.
#include "Nodes.h"
#include "Components.h"
#include "Element.h" // Assuming Element provides static utility functions
#include "ElementException.h"

// Definition of static member variables
std::map<std::string, Nodes> view::nodes;
std::vector<std::string> view::nodeNames;
std::map<std::string, Resistor> view::resistors;
std::vector<std::string> view::resistorsNames;
std::map<std::string, Capacitor> view::capacitors;
std::vector<std::string> view::capacitorNames;
std::map<std::string, Inductor> view::inductors;
std::vector<std::string> view::inductorNames;
std::map<std::string, Diode> view::Diodes;
std::vector<std::string> view::DiodeNames;
std::map<std::string, VoltageSource> view::voltageSources;
std::vector<std::string> view::voltageSourceName;
std::map<std::string, CurrentSource> view::currentSources;
std::vector<std::string> view::currentSourceName;
std::vector<std::string> view::components;

// Definition of static member functions
void view::addNode(std::vector<std::string> words) {
    if (words.size() != 3) {
        std::cerr << "Error: Syntax error\n";
        return;
    }
    std::string nodeName = words[2];
    Nodes N(nodeName);
    nodes[nodeName] = N;
    nodeNames.push_back(nodeName);
}

void view::show_NodesList(std::vector<std::string> NodeNames) {
    std::cout << "Available nodes:\n";
    if (NodeNames.empty()) {
        std::cout << "No nodes available.\n";
        return;
    }
    for (size_t i = 0; i < NodeNames.size(); ++i) {
        std::cout << NodeNames[i];
        if (i < NodeNames.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

bool view::renameNode(const std::string& oldName, const std::string& newName) {
    if (nodes.find(oldName) == nodes.end()) {
        std::cerr << "ERROR: Node " << oldName << " does not exist in the circuit\n";
        return false;
    }

    if (nodes.find(newName) != nodes.end()) {
        std::cerr << "ERROR: Node name " << newName << " already exists\n";
        return false;
    }
    nodes[oldName].changeNodeName(newName);

    nodes[newName] = nodes[oldName];
    nodes.erase(oldName);

    for (std::string& name : nodeNames) {
        if (name == oldName) {
            name = newName;
            break;
        }
    }
    std::cout << "SUCCESS: Node renamed from " << oldName << " to " << newName << std::endl;
    return true;
}

void view::addResistor(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "Resistor");
        }

        std::string name = words[1].substr(1);
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "Resistor");
        }

        if (resistors.find(name) != resistors.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "Resistor", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "Resistor");
        }

        double val = 0.0;
        int pow = -1;
        int trueValue = 0;
        Element::parsePhysicalValue(words[4], val, pow, trueValue);

        if (trueValue == -1) {
            throw ElementException(ElementException::INVALID_PHYSICAL_VALUE, "Resistor");
        }

        if (val <= 0 || pow == -1) {
            throw ElementException(ElementException::NONPOSITIVE_VALUE, "Resistor");
        }

        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }

        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }

        Resistor R(name, words[2], words[3], val, pow);
        resistors[name] = R;
        resistorsNames.push_back(name);
        components.push_back("R" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "Resistor " << name << " with resistance "
                  << val << "e" << pow << " added successfully between "
                  << words[2] << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "Resistor Error: " << e.what() << std::endl;
    }
}

void view::addCapacitor(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "Capacitor");
        }

        std::string name = words[1].substr(1);
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "Capacitor");
        }

        if (capacitors.find(name) != capacitors.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "Capacitor", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "Capacitor");
        }

        double val = 0.0;
        int pow = -1;
        int trueValue = 0;
        Element::parsePhysicalValue(words[4], val, pow, trueValue);
        if (trueValue == -1) {
            throw ElementException(ElementException::INVALID_PHYSICAL_VALUE, "Capacitor");
        }

        if (val <= 0 || pow == -1) {
            throw ElementException(ElementException::NONPOSITIVE_VALUE, "Capacitor");
        }

        // ادامه کد اصلی بدون تغییر
        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }
        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }
        Capacitor C(name, words[2], words[3], val, pow);
        capacitors[name] = C;
        capacitorNames.push_back(name);
        components.push_back("C" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "Capacitor " << name << " with capacitance " << val << "e" << pow
                  << " added successfully between " << words[2] << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "Capacitor Error: " << e.what() << std::endl;
    }
}


void view::addInductor(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "Inductor");
        }

        std::string name = words[1].substr(1);
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "Inductor");
        }

        if (inductors.find(name) != inductors.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "Inductor", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "Inductor");
        }

        double val = 0.0;
        int pow = -1;
        int trueValue = 0;
        Element::parsePhysicalValue(words[4], val, pow, trueValue);

        if (trueValue == -1) {
            throw ElementException(ElementException::INVALID_PHYSICAL_VALUE, "Inductor");
        }

        if (val <= 0 || pow == -1) {
            throw ElementException(ElementException::NONPOSITIVE_VALUE, "Inductor");
        }

        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }

        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }

        Inductor L(name, words[2], words[3], val, pow);
        inductors[name] = L;
        inductorNames.push_back(name);
        components.push_back("L" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "Inductor " << name << " with inductance "
                  << val << "e" << pow << " added successfully between "
                  << words[2] << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "Inductor Error: " << e.what() << std::endl;
    }
}


void view::addDiode(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "Diode");
        }

        std::string name = words[1].substr(1);
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "Diode");
        }

        if (Diodes.find(name) != Diodes.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "Diode", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "Diode");
        }

        std::string model = words[4];
        if (model != "D" && model != "Z") {
            throw ElementException(ElementException::INVALID_MODEL, "Diode", model);
        }

        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }

        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }

        double voltage = 0;
        if (model == "Z") {
            voltage = 0.7;
        }

        Diode D(name, words[2], words[3], voltage);
        Diodes[name] = D;
        DiodeNames.push_back(name);
        components.push_back("D" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "Diode " << name << " with model " << model
                  << " added successfully between " << words[2]
                  << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "Diode Error: " << e.what() << std::endl;
    }
}


void view::addGround(std::vector<std::string> words) {
    try {
        if (words.size() != 3) {
            throw ElementException(ElementException::SYNTAX_ERROR, "Ground");
        }

        std::string name = words[2];
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "Ground");
        }

        if (nodes.find(name) == nodes.end()) {
            Nodes N(name);
            nodes[name] = N;
            nodeNames.push_back(name);
        }

        nodes[name].setGround();
        components.push_back("GND");

        std::cout << "Node " << name << " set as ground.\n";
    }
    catch (const ElementException& e) {
        std::cerr << "Ground Error: " << e.what() << std::endl;
    }
}


void view::addVoltageSource(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "VoltageSource");
        }

        std::string name = words[1].substr(13); // "VoltageSource" is 13 chars
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "VoltageSource");
        }

        if (voltageSources.find(name) != voltageSources.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "VoltageSource", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "VoltageSource");
        }

        if (!Element::isValidDecimal(words[4])) {
            throw ElementException(ElementException::INVALID_PHYSICAL_VALUE, "VoltageSource", words[4]);
        }

        double val = 0.0;
        int pow = -1;
        int trueValue = 0;
        Element::extractPhysicalValue(words[4], val, pow, trueValue);

        if (val <= 0 || pow == -1) {
            throw ElementException(ElementException::NONPOSITIVE_VALUE, "VoltageSource");
        }

        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }

        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }

        VoltageSource V(name, words[2], words[3], val, pow);
        voltageSources[name] = V;
        voltageSourceName.push_back(name);
        components.push_back("V" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "VoltageSource " << name << " with voltage " << val << "e" << pow
                  << " added successfully between " << words[2] << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "VoltageSource Error: " << e.what() << std::endl;
    }
}


void view::addCurrentSource(std::vector<std::string> words) {
    try {
        if (words.size() != 5) {
            throw ElementException(ElementException::SYNTAX_ERROR, "CurrentSource");
        }

        std::string name = words[1].substr(13); // "CurrentSource" is 13 characters
        if (name.empty()) {
            throw ElementException(ElementException::EMPTY_NAME, "CurrentSource");
        }

        if (currentSources.find(name) != currentSources.end()) {
            throw ElementException(ElementException::DUPLICATE_ELEMENT, "CurrentSource", name);
        }

        if (words[2] == words[3]) {
            throw ElementException(ElementException::SAME_NODES, "CurrentSource");
        }

        if (!Element::isValidDecimal(words[4])) {
            throw ElementException(ElementException::INVALID_PHYSICAL_VALUE, "CurrentSource", words[4]);
        }

        double val = 0.0;
        int pow = -1;
        int trueValue = 0;
        Element::extractPhysicalValue(words[4], val, pow, trueValue);

        if (val <= 0 || pow == -1) {
            throw ElementException(ElementException::NONPOSITIVE_VALUE, "CurrentSource");
        }

        if (nodes.find(words[2]) == nodes.end()) {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }

        if (nodes.find(words[3]) == nodes.end()) {
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }

        CurrentSource C(name, words[2], words[3], val, pow);
        currentSources[name] = C;
        currentSourceName.push_back(name);
        components.push_back("I" + name);
        nodes[words[2]].addConnectedNode(words[3]);
        nodes[words[3]].addConnectedNode(words[2]);

        std::cout << "CurrentSource " << name << " with current " << val << "e" << pow
                  << " added successfully between " << words[2] << " & " << words[3] << '.' << std::endl;
    }
    catch (const ElementException& e) {
        std::cerr << "CurrentSource Error: " << e.what() << std::endl;
    }
}


void view::addSinusoidalSource(std::vector<std::string> words) {
    // This function was empty in the provided code.
    // Implement its logic here if needed.
    std::cerr << "Error: Sinusoidal source not implemented.\n";
}

void view::deleteResistor(std::string name) {
    if (resistors.find(name) == resistors.end()) {
        std::cerr << "Error: Cannot delete resistor; component not found\n";
        return;
    }
    std::string node1 = resistors[name].getNode1();
    std::string node2 = resistors[name].getNode2();
    nodes[node1].removeConnectedNod(node2);
    nodes[node2].removeConnectedNod(node1);
    resistorsNames.erase(std::remove(resistorsNames.begin(), resistorsNames.end(), name), resistorsNames.end());
    // Also remove from general 'components' list if applicable
    components.erase(std::remove(components.begin(), components.end(), "R" + name), components.end());
    resistors.erase(name);
    std::cout << "Resistor " << name << " deleted successful." << std::endl;
}

void view::deleteCapacitor(std::string name) {
    if (capacitors.find(name) == capacitors.end()) {
        std::cerr << "Error: Cannot delete capacitor; component not found\n";
        return;
    }
    std::string node1 = capacitors[name].getNode1();
    std::string node2 = capacitors[name].getNode2();
    nodes[node1].removeConnectedNod(node2);
    nodes[node2].removeConnectedNod(node1);
    capacitorNames.erase(std::remove(capacitorNames.begin(), capacitorNames.end(), name), capacitorNames.end());
    // Also remove from general 'components' list if applicable
    components.erase(std::remove(components.begin(), components.end(), "C" + name), components.end());
    capacitors.erase(name);
    std::cout << "Capacitor " << name << " deleted successful." << std::endl;
}

void view::deleteInductor(std::string name) {
    if (inductors.find(name) == inductors.end()) {
        std::cerr << "Error: Cannot delete inductor; component not found\n";
        return;
    }
    std::string node1 = inductors[name].getNode1();
    std::string node2 = inductors[name].getNode2();
    nodes[node1].removeConnectedNod(node2);
    nodes[node2].removeConnectedNod(node1);
    inductorNames.erase(std::remove(inductorNames.begin(), inductorNames.end(), name), inductorNames.end());
    // Also remove from general 'components' list if applicable
    components.erase(std::remove(components.begin(), components.end(), "L" + name), components.end());
    inductors.erase(name);
    std::cout << "Inductor " << name << " deleted successful." << std::endl;
}

void view::deleteDiode(std::string name) {
    if (Diodes.find(name) == Diodes.end()) {
        std::cerr << "Error: Cannot delete diode; component not found\n";
        return;
    }
    std::string node1 = Diodes[name].getNode1();
    std::string node2 = Diodes[name].getNode2();
    nodes[node1].removeConnectedNod(node2);
    nodes[node2].removeConnectedNod(node1);
    DiodeNames.erase(std::remove(DiodeNames.begin(), DiodeNames.end(), name), DiodeNames.end());
    // Also remove from general 'components' list if applicable
    components.erase(std::remove(components.begin(), components.end(), "D" + name), components.end());
    Diodes.erase(name);
    std::cout << "Diode " << name << " deleted successful." << std::endl;
}

void view::displayComponents() {
    if (components.empty()) { // Use .empty() for better readability
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << components[i];
        if (i < components.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayResistors() {
    if (resistorsNames.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < resistorsNames.size(); ++i) {
        std::cout << "R" << resistorsNames[i];
        if (i < resistorsNames.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayCapacitors() {
    if (capacitorNames.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < capacitorNames.size(); ++i) {
        std::cout << "C" << capacitorNames[i];
        if (i < capacitorNames.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayInductors() {
    if (inductorNames.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < inductorNames.size(); ++i) {
        std::cout << "L" << inductorNames[i];
        if (i < inductorNames.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayDiodes() {
    if (DiodeNames.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < DiodeNames.size(); ++i) {
        std::cout << "D" << DiodeNames[i];
        if (i < DiodeNames.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayVoltageSources() {
    if (voltageSourceName.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < voltageSourceName.size(); ++i) {
        std::cout << "V" << voltageSourceName[i];
        if (i < voltageSourceName.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::displayCurrentSources() {
    if (currentSourceName.empty()) {
        std::cerr << "empty!\n";
        return;
    }
    for (size_t i = 0; i < currentSourceName.size(); ++i) {
        std::cout << "I" << currentSourceName[i];
        if (i < currentSourceName.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void view::input_handelling(std::vector<std::string> words) {
    if (words.empty()) {
        std::cerr << "Error: Empty command\n";
        return;
    }

    if (words.size() >= 3 && words[0] == "add" && words[1] == "node") {
        view::addNode(words);
    } else if (words[0] == ".rename") {
        if (words.size() == 4 && words[1] == "node") {
            renameNode(words[2], words[3]);
        } else {
            std::cerr << "ERROR: Invalid syntax - correct format:\n" << ".rename node <old_name> <new_name>\n";
        }
    } else if (words.size() == 1 && words[0] == ".nodes") {
        view::show_NodesList(nodeNames);
    } else if (words.size() >= 3 && words[0] == "add") {
        if (!words[1].empty()) { // Ensure words[1] is not empty before accessing its first character
            if (words[1][0] == 'R') {
                addResistor(words);
            } else if (words[1][0] == 'C') {
                if (words[1].length() >= 13 && words[1].substr(0, 13) == "CurrentSource") { // Check length to avoid out_of_range
                    addCurrentSource(words);
                } else {
                    addCapacitor(words);
                }
            } else if (words[1][0] == 'L') {
                addInductor(words);
            } else if (words[1][0] == 'D') {
                addDiode(words);
            } else if (words[1] == "GND") {
                addGround(words);
            } else if (words[1][0] == 'V') {
                if (words[1].length() >= 13 && words[1].substr(0, 13) == "VoltageSource") {
                    addVoltageSource(words);
                } else {
                    std::cerr << "Error: Syntax Error. Unexpected Voltage Source format.\n";
                }
            } else {
                std::cerr << "Error: Element " << words[1].substr(1) << " not found in library\n";
            }
        } else {
            std::cerr << "Error: Empty element type in 'add' command.\n";
        }
    } else if (words.size() == 2 && words[0] == "delete") {
        if (!words[1].empty()) {
            if (words[1][0] == 'R') {
                deleteResistor(words[1].substr(1));
            } else if (words[1][0] == 'C') {
                deleteCapacitor(words[1].substr(1));
            } else if (words[1][0] == 'L') {
                deleteInductor(words[1].substr(1));
            } else if (words[1][0] == 'D') {
                deleteDiode(words[1].substr(1));
            } else {
                std::cerr << "Error: Invalid component type for delete.\n";
            }
        } else {
            std::cerr << "Error: Empty component name in 'delete' command.\n";
        }
    } else if (words[0] == ".list") {
        if (words.size() == 1) {
            displayComponents();
        } else if (words.size() == 2) {
            if (words[1] == "R") {
                displayResistors();
            } else if (words[1] == "L") {
                displayInductors();
            } else if (words[1] == "D") {
                displayDiodes();
            } else if (words[1] == "C") {
                displayCapacitors();
            } else if (words[1] == "V") {
                displayVoltageSources();
            } else if (words[1] == "I") {
                displayCurrentSources();
            } else {
                std::cerr << "Error: Invalid list command argument.\n";
            }
        } else {
            std::cerr << "Error: Syntax error for .list command.\n";
        }
    } else {
        std::cerr << "Error: Syntax error\n";
    }
}
#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> // Required for std::remove

// Forward declarations of classes used in 'view'
// You will need to define these classes (Nodes, Resistor, Capacitor, Inductor, Diode, VoltageSource, CurrentSource, Element)
// in their respective header files.
class Nodes;
class Resistor;
class Capacitor;
class Inductor;
class Diode;
class VoltageSource;
class CurrentSource;
class Element; // Assuming Element has static methods like parsePhysicalValue and extractPhysicalValue

class view {
public:
    // Static member variables (must be defined in .cpp file)
    static std::map<std::string, Nodes> nodes;
    static std::vector<std::string> nodeNames;
    static std::map<std::string, Resistor> resistors;
    static std::vector<std::string> resistorsNames;
    static std::map<std::string, Capacitor> capacitors;
    static std::vector<std::string> capacitorNames;
    static std::map<std::string, Inductor> inductors;
    static std::vector<std::string> inductorNames;
    static std::map<std::string, Diode> Diodes;
    static std::vector<std::string> DiodeNames;
    static std::map<std::string, VoltageSource> voltageSources;
    static std::vector<std::string> voltageSourceName;
    static std::map<std::string, CurrentSource> currentSources;
    static std::vector<std::string> currentSourceName;
    static std::vector<std::string> components; // List of all component names (e.g., "R1", "C2")

    // Static member functions
    static void addNode(std::vector<std::string> words);
    static void show_NodesList(std::vector<std::string> NodeNames);
    static bool renameNode(const std::string& oldName, const std::string& newName);
    static void addResistor(std::vector<std::string> words);
    static void addCapacitor(std::vector<std::string> words);
    static void addInductor(std::vector<std::string> words);
    static void addDiode(std::vector<std::string> words);
    static void addGround(std::vector<std::string> words);
    static void addVoltageSource(std::vector<std::string> words);
    static void addCurrentSource(std::vector<std::string> words);
    static void addSinusoidalSource(std::vector<std::string> words); // Empty in the provided code

    static void deleteResistor(std::string name);
    static void deleteCapacitor(std::string name);
    static void deleteInductor(std::string name);
    static void deleteDiode(std::string name);

    static void displayComponents();
    static void displayResistors();
    static void displayCapacitors();
    static void displayInductors();
    static void displayDiodes();
    static void displayVoltageSources();
    static void displayCurrentSources();

    static void input_handelling(std::vector<std::string> words);
};

#endif // VIEW_H
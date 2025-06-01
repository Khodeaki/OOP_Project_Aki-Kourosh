#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Element.h"

class Resistor : public Element {
public:
    Resistor() : Element() {}
    Resistor(string NAme, string Node1, string Node2, double Value, int Pow)
            : Element(NAme, Node1, Node2, Value, Pow) {}
};

class Capacitor : public Element {
public:
    Capacitor() : Element() {}
    Capacitor(string NAme, string Node1, string Node2, double Value, int Pow)
            : Element(NAme, Node1, Node2, Value, Pow) {}
};

class Inductor : public Element {
public:
    Inductor() : Element() {}
    Inductor(string NAme, string Node1, string Node2, double Value, int Pow)
            : Element(NAme, Node1, Node2, Value, Pow) {}
};

class Diode : public Element {
public:
    Diode() : Element() {}
    Diode(string NAme, string Node1, string Node2, double Voltage)
            : Element(NAme, Node1, Node2, Voltage, 0) {}
};

class VoltageSource : public Element {
public:
    VoltageSource() : Element() {}
    VoltageSource(string NAme, string Node1, string Node2, double Voltage, int pow)
            : Element(NAme, Node1, Node2, Voltage, pow) {}
};

class CurrentSource : public Element {
public:
    CurrentSource() : Element() {}
    CurrentSource(string NAme, string Node1, string Node2, double current, int pow)
            : Element(NAme, Node1, Node2, current, pow) {}
};

class SinusoidalSource : public VoltageSource {
    // Define custom behavior later if needed
};

#endif // COMPONENTS_H

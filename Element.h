#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include <regex>

using namespace std;

class Element {
protected:
    string Name;
    string Node1Name;
    string Node2Name;
    double value;
    int pow10;

public:
    Element();
    Element(string NAme, string Node1, string Node2, double Value, int Pow);

    static void parsePhysicalValue(const string& input, double& value, int& pow10, int& trueValue);
    static void extractPhysicalValue(const string& input, double& value, int& pow10, int& trueValue);
    static bool isValidDecimal(const string& input);

    string getNode1();
    string getNode2();
};

#endif // ELEMENT_H

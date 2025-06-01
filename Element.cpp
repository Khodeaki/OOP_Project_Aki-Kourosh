#include "Element.h"

Element::Element() : Name(""), Node1Name(""), Node2Name(""), value(0.0), pow10(0) {}

Element::Element(string NAme, string Node1, string Node2, double Value, int Pow)
        : Name(NAme), Node1Name(Node1), Node2Name(Node2), value(Value), pow10(Pow) {}

void Element::parsePhysicalValue(const string& input, double& value, int& pow10, int& trueValue) {
    regex pattern(R"(^\s*([+-]?\d+(\.\d+)?)([a-zA-Z]+|e[+-]?\d+)?\s*$)");
    smatch match;

    if (!regex_match(input, match, pattern)) {
        cerr << "Error: invalid value" << endl;
        trueValue = -1;
        return;
    }

    try {
        value = stod(match[1]);
    } catch (...) {
        cerr << "Error: Syntax error" << endl;
        return;
    }

    string suffix = match[3];

    if (suffix.empty()) {
        pow10 = 0;
    } else if (suffix == "K" || suffix == "k") {
        pow10 = 3;
    } else if (suffix == "M" || suffix == "Meg") {
        pow10 = 6;
    } else if (suffix == "u") {
        pow10 = -6;
    } else if (suffix == "n") {
        pow10 = -9;
    } else if (suffix == "m") {
        pow10 = -3;
    } else if (suffix[0] == 'e') {
        try {
            pow10 = stoi(suffix.substr(1));
        } catch (...) {
            cerr << "Error: Syntax error" << endl;
            return;
        }
    } else {
        cerr << "Error: Syntax error" << endl;
        return;
    }
}

void Element::extractPhysicalValue(const string& input, double& value, int& pow10, int& trueValue) {
    regex pattern(R"(^\s*([+-]?\d+(\.\d+)?)([a-zA-Z]+|e[+-]?\d+)?\s*$)");
    smatch match;

    if (!regex_match(input, match, pattern)) {
        trueValue = -1;
        return;
    }

    try {
        value = stod(match[1]);
    } catch (...) {
        trueValue = -1;
        return;
    }

    string suffix = match[3];
    trueValue = 1;

    if (suffix.empty()) {
        pow10 = 0;
    } else if (suffix == "K" || suffix == "k") {
        pow10 = 3;
    } else if (suffix == "M" || suffix == "Meg") {
        pow10 = 6;
    } else if (suffix == "u") {
        pow10 = -6;
    } else if (suffix == "n") {
        pow10 = -9;
    } else if (suffix == "m") {
        pow10 = -3;
    } else if (suffix[0] == 'e') {
        try {
            pow10 = stoi(suffix.substr(1));
        } catch (...) {
            trueValue = -1;
            return;
        }
    } else {
        trueValue = -1;
        return;
    }
}

bool Element::isValidDecimal(const string& input) {
    regex pattern(R"(^[+-]?(\d+(\.\d*)?|\.\d+)$)");
    return regex_match(input, pattern);
}

string Element::getNode1() {
    return Node1Name;
}

string Element::getNode2() {
    return Node2Name;
}

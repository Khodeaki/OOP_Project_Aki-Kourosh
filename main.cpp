#include <bits/stdc++.h>

using namespace std;

class Nodes {
private:
    string nodeName;
    double nodeVoltage;
    vector<string> connectedNodes;
public:
    Nodes() : nodeName(""), nodeVoltage(0.0) {}

    Nodes(string name, double v = 0.0) : nodeName(name), nodeVoltage(v) {}

    void changeNodeName(string newName) {
        nodeName = newName;
    }

    string getNodeName() {
        return nodeName;
    }
};


class Element {
protected:
    string Name ;
    string Node1Name ;
    string Node2Name ;
    double value ;
    int pow10 ;

public:
    Element() : Name("") , Node1Name("") , Node2Name("") , value(0.0) , pow10(0) {}
    Element (string NAme , string Node1 , string Node2 , double Value , int Pow) : Name(NAme) , Node1Name(Node1) , Node2Name(Node2) , value(Value) , pow10(Pow) {}

    static void parsePhysicalValue(const string& input, double& value, int& pow10) {
        regex pattern(R"(^\s*([+-]?\d+(\.\d+)?)([a-zA-Z]+|e\d+)?\s*$)");
        smatch match;
        if (regex_match(input, match, pattern)) {
            value = std::stod(match[1]);

            string suffix = match[3];

            if (suffix.empty()) {
                pow10 = 0;
            } else if (suffix == "K") {
                pow10 = 3;
            } else if (suffix == "M" || suffix == "Meg") {
                pow10 = 6;
            } else if (suffix[0] == 'e') {
                try {
                    pow10 = stoi(suffix.substr(1));
                } catch (...) {
                    pow10 = 0;
                }
            } else {
                pow10 = 0 ;
            }
        } else {
            throw invalid_argument("Invalid input format: " + input);
        }
    }
};


class Resistor : public Element {
public:
    Resistor() : Element() {}
    Resistor(string NAme, string Node1, string Node2, double Value, int Pow)
            : Element(NAme, Node1, Node2, Value, Pow) {}
};


class Capacitor : public  Element {
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
    Diode(string NAme, string Node1, string Node2, double Value, int Pow)
    : Element(NAme, Node1, Node2, Value, Pow) {}
};






map<string, Nodes> nodes;
vector<string> nodeNames;
class view {
public:
    static void addNode (const string & nodeName){
        Nodes N(nodeName);
        nodes[nodeName] = N;
        nodeNames.push_back(nodeName);
    }
    static void show_NodesList(vector<string> NodeNames) {
        cout << "Available nodes:\n";
        for (int i = 0; i < NodeNames.size() - 1; i++) {
            cout << NodeNames[i] << ", ";
        }
        cout << NodeNames[NodeNames.size() - 1] << endl;
    }
    static bool renameNode(const string& oldName, const string& newName) {
        if (nodes.find(oldName) == nodes.end()) {
            cerr << "ERROR: Node " << oldName << " does not exist in the circuit\n";
            return false;
        }

        if (nodes.find(newName) != nodes.end()) {
            cerr << "ERROR: Node name " << newName << " already exists\n";
            return false;
        }
        nodes[oldName].changeNodeName(newName);

        nodes[newName] = nodes[oldName];
        nodes.erase(oldName);

        for (string& name : nodeNames) {
            if (name == oldName) {
                name = newName;
                break;
            }
        }
        cout << "SUCCESS: Node renamed from " << oldName << " to " << newName << endl;
        return true;
    }
    static void addResistor (vector <string> words) {
        string name = words[1].substr(1);
        double val = 0.0;
        int pow = -1 ;
        Element::parsePhysicalValue(words[4] , val , pow) ;
        if (val <= 0 || pow == -1){
            cerr << "Error: Resistance cannot be zero or negative\n" ;
            return;
        }
        // barresi tekrari naboodan esm moghavemat
        Resistor R(name , words[2] , words[3] , val , pow) ;
    }

    static void input_handelling(vector<string> words) {
        if (words.size() >= 3 && words[0] == "add" && words[1] == "node") {
            view::addNode(words[2]) ;
        }
        else if (words[0] == ".rename") {
            if (words[1] == "node") {
                if (words.size() != 4) {
                    cerr << "ERROR: Invalid syntax - correct format:\n";
                    return;
                }
                renameNode(words[2], words[3]);
            }
            cerr << "ERROR: Invalid syntax - correct format:\n";
            return;
        }
        else if (words.size() == 1 && words[0] == ".nodes") {
            view::show_NodesList(nodeNames);
        }
        else if (words.size() == 5 && words[0] == "add" ){
            if(words[1][0] == 'R'){
                addResistor(words) ;
            }
            else {
                cerr << "Error: Element "<< words[1].substr(1) <<" not found in library\n" ;
            }
            // put all adds here
        }
        else if (words.size() == 2 && words[0] == "delete"){
            if (words[1][0] == 'R'){
                // delete the R after checking
            }
        }
        else {
            cerr << "Error: Syntax error\n";
        }
    }

};


std::vector<std::string> processInputToVector(const std::string& input) {
    std::vector<std::string> words;
    std::regex word_regex("\\S+");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it) {
        words.push_back(it->str());
    }
    return words;
}



int main() {
    string inp;
    while (getline(cin, inp)) {
        vector<string> words = processInputToVector(inp);
        if (words[0] == "end") {
            break;
        }
        if (words.size() == 0) continue;
        view::input_handelling(words);
    }


    return 0;
}
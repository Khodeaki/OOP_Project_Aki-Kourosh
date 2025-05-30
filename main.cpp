#include <bits/stdc++.h>

using namespace std;

class Nodes {
private:
    string nodeName;
    double nodeVoltage;
    vector<string> connectedNodes; // nodes remain after deleting components so we have to delete them if the size is 0 .
public:
    Nodes() : nodeName(""), nodeVoltage(0.0) {}

    Nodes(string name, double v = 0.0) : nodeName(name), nodeVoltage(v) {}

    void changeNodeName(string newName) {
        nodeName = newName;
    }

    string getNodeName() {
        return nodeName;
    }
    void addConnectedNode (string name){
        connectedNodes.push_back(name) ;
    }
    void removeConnectedNod (string name){
        connectedNodes.erase(remove(connectedNodes.begin(), connectedNodes.end(), name), connectedNodes.end());
    }
};


class Element {
protected:
    string Name ;
    string Node1Name ;
    string Node2Name ;
    double value ; // baraye diode voltage roshan shodan   D:0   Z:0.7
    int pow10 ; // baraye diode 0

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
            } else if (suffix == "K" || suffix == "k") {
                pow10 = 3;
            } else if (suffix == "M" || suffix == "Meg") {
                pow10 = 6;
            } else if (suffix == "u"){
                pow10 = -6;
            } else if (suffix == "n"){
                pow10 = -12;
            } else if (suffix == "m"){
                pow10 = -3;
            }
            else if (suffix[0] == 'e') {
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

    string getNode1 () {return Node1Name ;}
    string getNode2 () {return Node2Name ;}

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
    Diode(string NAme, string Node1, string Node2, double Voltage)
    : Element(NAme, Node1, Node2, Voltage, 0) {}
};






map <string , Nodes> nodes ;
vector <string> nodeNames ;
map <string , Resistor> resistors ;
vector <string> resistorsNames ;
map <string , Capacitor> capacitors ;
vector <string>  capacitorNames ;
map <string , Inductor> inductors ;
vector <string> inductorNames ;
map <string , Diode> Diodes ;
vector <string> DiodeNames ;


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
        if (resistors.find(name) != resistors.end()){
            cerr << "Error: Resistor " << name << " already exists in the circuit\n" ;
            return;
        }
        if (nodes.find(words[2]) == nodes.end()){
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }
        if (nodes.find(words[3]) == nodes.end()){
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }
        Resistor R(name , words[2] , words[3] , val , pow) ;
        resistors[name] = R ;
        resistorsNames.push_back(name) ;
        nodes[words[2]].addConnectedNode(words[3]) ;
        nodes[words[3]].addConnectedNode(words[2]) ;
        cout << "Resistor " << name << " with resistance " << val << "e" << pow << " added successful between " << words[2] << " & " << words[3] << '.' << endl;
    }
    static void addCapacitor (vector <string> words) {
        string name = words[1].substr(1);
        double val = 0.0;
        int pow = -1 ;
        Element::parsePhysicalValue(words[4] , val , pow) ;
        if (val <= 0 || pow == -1){
            cerr << "Error: Capacitor cannot be zero or negative\n" ;
            return;
        }
        if (capacitors.find(name) != capacitors.end()){
            cerr << "Error: Capacitor " << name << " already exists in the circuit\n" ;
            return;
        }
        if (nodes.find(words[2]) == nodes.end()){
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }
        if (nodes.find(words[3]) == nodes.end()){
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }
        Capacitor C(name , words[2] , words[3] , val , pow) ;
        capacitors[name] = C ;
        capacitorNames.push_back(name) ;
        nodes[words[2]].addConnectedNode(words[3]) ;
        nodes[words[3]].addConnectedNode(words[2]) ;
        cout << "Capacitor " << name << " with capacitance " << val << "e" << pow << " added successful between " << words[2] << " & " << words[3] << '.' << endl;
    }

    static void addInductor (vector <string> words) {
        string name = words[1].substr(1);
        double val = 0.0;
        int pow = -1 ;
        Element::parsePhysicalValue(words[4] , val , pow) ;
        if (val <= 0 || pow == -1){
            cerr << "Error: Inductor cannot be zero or negative\n" ;
            return;
        }
        if (inductors.find(name) != inductors.end()){
            cerr << "Error: inductor " << name << " already exists in the circuit\n" ;
            return;
        }
        if (nodes.find(words[2]) == nodes.end()){
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }
        if (nodes.find(words[3]) == nodes.end()){
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }
        Inductor L(name , words[2] , words[3] , val , pow) ;
        inductors[name] = L ;
        inductorNames.push_back(name) ;
        nodes[words[2]].addConnectedNode(words[3]) ;
        nodes[words[3]].addConnectedNode(words[2]) ;
        cout << "Inductor " << name << " with inductance " << val << "e" << pow << " added successful between " << words[2] << " & " << words[3] << '.' << endl;
    }

    static void addDiode (vector <string> words) {
        string name = words[1].substr(1);
        string model = words[4] ;
        if (model != "D" && model !="Z"){
            cerr << "Error: Model "<<model<<" not found in library" ;
            return;
        }
        if (Diodes.find(name) != Diodes.end()){
            cerr << "Error: diode " << name << " already exists in the circuit\n" ;
            return;
        }
        if (nodes.find(words[2]) == nodes.end()){
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
        }
        if (nodes.find(words[3]) == nodes.end()){
            Nodes N(words[3]);
            nodes[words[3]] = N;
            nodeNames.push_back(words[3]);
        }
        double voltage = 0 ;
        if (model == "Z") {voltage = 0.7 ;}
        Diode D(name , words[2] , words[3] , voltage) ;
        Diodes[name] = D ;
        DiodeNames.push_back(name) ;
        nodes[words[2]].addConnectedNode(words[3]) ;
        nodes[words[3]].addConnectedNode(words[2]) ;
        cout << "diode " << name << " with model " << model << " added successful between " << words[2] << " & " << words[3] << '.' << endl;
    }

    static void deleteResistor (string name) {
        if (resistors.find(name) == resistors.end()){
            cerr << "Error: Cannot delete resistor; component not found\n" ;
            return ;
        }
        string node1 = resistors[name].getNode1() ;
        string node2 = resistors[name].getNode2() ;
        nodes[node1].removeConnectedNod(node2);
        nodes[node2].removeConnectedNod(node1);
        resistorsNames.erase(remove(resistorsNames.begin(), resistorsNames.end(), name), resistorsNames.end());
        resistors.erase(name) ;
        cout << "Resistor " << name << " deleted successful." << endl;
    }

    static void deleteCapacitor (string name) {
        if (capacitors.find(name) == capacitors.end()){
            cerr << "Error: Cannot delete capacitor; component not found\n" ;
            return ;
        }
        string node1 = capacitors[name].getNode1() ;
        string node2 = capacitors[name].getNode2() ;
        nodes[node1].removeConnectedNod(node2);
        nodes[node2].removeConnectedNod(node1);
        capacitorNames.erase(remove(capacitorNames.begin(), capacitorNames.end(), name), capacitorNames.end());
        capacitors.erase(name) ;
        cout << "Capacitor " << name << " deleted successful." << endl;
    }

    static void deleteInductor (string name) {
        if (inductors.find(name) == inductors.end()){
            cerr << "Error: Cannot delete inductor; component not found\n" ;
            return ;
        }
        string node1 = inductors[name].getNode1() ;
        string node2 = inductors[name].getNode2() ;
        nodes[node1].removeConnectedNod(node2);
        nodes[node2].removeConnectedNod(node1);
        inductorNames.erase(remove(inductorNames.begin(), inductorNames.end(), name), inductorNames.end());
        inductors.erase(name) ;
        cout << "Inductor " << name << " deleted successful." << endl;
    }

    static void deleteDiode (string name) {
        if (Diodes.find(name) == Diodes.end()){
            cerr << "Error: Cannot delete diode; component not found\n" ;
            return ;
        }
        string node1 = Diodes[name].getNode1() ;
        string node2 = Diodes[name].getNode2() ;
        nodes[node1].removeConnectedNod(node2);
        nodes[node2].removeConnectedNod(node1);
        DiodeNames.erase(remove(DiodeNames.begin(), DiodeNames.end(), name), DiodeNames.end());
        Diodes.erase(name) ;
        cout << "Diode " << name << " deleted successful." << endl;
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
            if (words[1][0] == 'R'){
                addResistor(words) ;
            } else if (words[1][0] == 'C'){
                addCapacitor(words) ;
            } else if (words[1][0] == 'L'){
                addInductor(words) ;
            } else if (words[1][0] == 'D'){
                addDiode(words) ;
            }
            else {
                cerr << "Error: Element "<< words[1].substr(1) <<" not found in library\n" ;
            }
            // put all adds here
        }
        else if (words.size() == 2 && words[0] == "delete"){
            if (words[1][0] == 'R'){
                deleteResistor(words[1].substr(1)) ;
            } else if (words[1][0] == 'C'){
                deleteCapacitor(words[1].substr(1)) ;
            } else if (words[1][0] == 'L'){
                deleteInductor(words[1].substr(1)) ;
            } else if (words[1][0] == 'D'){
                deleteDiode(words[1].substr(1)) ;
            }
            else {
                cerr << "Error: Syntax error\n";
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
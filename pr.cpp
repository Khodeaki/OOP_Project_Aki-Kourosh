#include <bits/stdc++.h>
//yoyo
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
    string type;
    string Name;
    string Node1Name;
    string Node2Name;
    double value;
};


map<string, Nodes> nodes;
vector<string> nodeNames;
class view {
public:
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

    static void input_handelling(vector<string> words) {
        if (words.size() >= 3 && words[0] == "add" && words[1] == "node") {
            Nodes N(words[2]);
            nodes[words[2]] = N;
            nodeNames.push_back(words[2]);
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
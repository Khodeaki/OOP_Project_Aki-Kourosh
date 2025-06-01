#include <bits/stdc++.h>
#include "Nodes.h"
#include "Element.h"
#include "Components.h"
#include "view.h"
#include "ElementException.h"
using namespace std;

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

        if (words.empty()) continue;

        if (words[0] == "end") {
            break;
        }

        view::input_handelling(words);
    }

    return 0;
}

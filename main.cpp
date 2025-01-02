#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dictionary {
private:
    vector<string> words;
    vector<string> definitions;

public:
    void addWord(const string &word, const string &definition) {
        words.push_back(word);
        definitions.push_back(definition);
    }

    void printWords() {
        for (size_t i = 0; i < words.size(); ++i) {
            cout << words[i] << ": " << definitions[i] << endl;
        }
    }
};

int main() {
    Dictionary dict;
    dict.addWord("example", "a representative form or pattern");
    dict.addWord("test", "a procedure intended to establish the quality, performance, or reliability of something");

    dict.printWords();

    return 0;
}

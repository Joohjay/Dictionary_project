#include <iostream>
#include <map>
#include <string>

using namespace std;

class Dictionary {
private:
    map<string, string> dictionary;

public:
    void addWord(const string &word, const string &definition) {
        dictionary[word] = definition;
    }
};

int main() {

    return 0;
}
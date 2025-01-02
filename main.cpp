#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Dictionary {
private:
    string filepath;

public:
    Dictionary(const string &path) : filepath(path) {}

    void addWordToFile(const string &word, const string &definition) {
        ofstream file;
        file.open(filepath, ios::app);
        if (file.is_open()) {
            file << word << ":" << definition << endl;
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    string searchWordInFile(const string &word) {
        ifstream file(filepath);
        string line, foundDefinition = "Word not found!";
        if (file.is_open()) {
            while (getline(file, line)) {
                size_t pos = line.find(':');
                if (pos != string::npos) {
                    string fileWord = line.substr(0, pos);
                    string fileDefinition = line.substr(pos + 1);
                    if (fileWord == word) {
                        foundDefinition = fileDefinition;
                        break;
                    }
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
        return foundDefinition;
    }
};

int main() {
    Dictionary dict("vocabulary.txt");

    // Add words to the file
    dict.addWordToFile("example", "a representative form or pattern");
    dict.addWordToFile("test", "a procedure intended to establish the quality, performance, or reliability of something");

    // Search for words
    string wordToSearch = "example";
    cout << "Definition of " << wordToSearch << ": " << dict.searchWordInFile(wordToSearch) << endl;

    wordToSearch = "test";
    cout << "Definition of " << wordToSearch << ": " << dict.searchWordInFile(wordToSearch) << endl;

    return 0;
}

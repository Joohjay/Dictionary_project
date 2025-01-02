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

    void addWordToFile(const string &word, const vector<string> &definitions) {
        ofstream file;
        file.open(filepath, ios::app);
        if (file.is_open()) {
            for (const auto &definition : definitions) {
                file << word << ":" << definition << endl;
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    vector<string> searchWordInFile(const string &word) {
        ifstream file(filepath);
        string line;
        vector<string> foundDefinitions;
        if (file.is_open()) {
            while (getline(file, line)) {
                size_t pos = line.find(':');
                if (pos != string::npos) {
                    string fileWord = line.substr(0, pos);
                    string fileDefinition = line.substr(pos + 1);
                    if (fileWord == word) {
                        foundDefinitions.push_back(fileDefinition);
                    }
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
        return foundDefinitions.empty() ? vector<string>{"Word not found!"} : foundDefinitions;
    }
};

void displayMenu() {
    cout << "Dictionary Menu" << endl;
    cout << "1. Add a word" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Dictionary dict("vocabulary.txt");
    int choice;
    string word, definition;
    vector<string> definitions;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cin.ignore(); // To ignore the leftover newline character
                {
                    vector<string> existingDefinitions = dict.searchWordInFile(word);
                    if (!existingDefinitions.empty() && existingDefinitions[0] != "Word not found!") {
                        cout << "Word already exists with the following definitions:" << endl;
                        for (const auto &def : existingDefinitions) {
                            cout << "- " << def << endl;
                        }
                        cout << "Enter additional definitions (or type 'done' to finish): ";
                    } else {
                        cout << "Enter definitions (or type 'done' to finish): ";
                    }
                }
                do {
                    getline(cin, definition);
                    if (definition != "done") {
                        definitions.push_back(definition);
                    }
                } while (definition != "done");
                dict.addWordToFile(word, definitions);
                cout << "Word added successfully!" << endl;
                definitions.clear(); // Clear definitions for next word
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                cin.ignore(); // To ignore the leftover newline character
                {
                    vector<string> results = dict.searchWordInFile(word);
                    cout << "Definitions of " << word << ":" << endl;
                    for (const auto &def : results) {
                        cout << "- " << def << endl;
                    }
                }
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
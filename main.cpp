#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Dictionary {
private:
    string filepath;

public:
    Dictionary(const string &path) : filepath(path) {}

    void addWordToFile(const string &word, const vector<string> &definitions) {
        ofstream file;
        try {
            file.open(filepath, ios::app);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for writing.");
            }
            file << "====================================" << endl;
            for (const auto &definition : definitions) {
                file << word << ":\t" << definition << endl;
            }
            file.close();
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }

    vector<string> searchWordInFile(const string &word) {
        ifstream file;
        string line;
        vector<string> foundDefinitions;
        try {
            file.open(filepath);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for reading.");
            }
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
        } catch (const exception &e) {
            cerr << e.what() << endl;
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
        if (!(cin >> choice)) {
            cerr << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cin.ignore();
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
                definitions.clear();
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                cin.ignore();
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
                cerr << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
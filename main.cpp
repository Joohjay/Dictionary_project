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

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter definition: ";
                cin.ignore(); // To ignore the leftover newline character
                getline(cin, definition);
                dict.addWordToFile(word, definition);
                cout << "Word added successfully!" << endl;
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                cout << "Definition of " << word << ": " << dict.searchWordInFile(word) << endl;
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
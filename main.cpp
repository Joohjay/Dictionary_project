#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Class to manage dictionary operations
class Dictionary {
private:
    string filepath; // File path to store dictionary data

public:
    // Constructor to initialize the file path
    Dictionary(const string &path) : filepath(path) {}

    // Function to add a word and its definitions to the file
    void addWordToFile(const string &word, const vector<string> &definitions) {
        ofstream file;
        try {
            file.open(filepath, ios::app); // Open file in append mode
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for writing.");
            }
            file << "====================================" << endl; // Add separator line
            for (const auto &definition : definitions) {
                file << word << ":\t" << definition << endl; // Write word and definition
            }
            file.close();
        } catch (const exception &e) {
            cerr << e.what() << endl; // Display error message
        }
    }

    // Function to search for a word in the file and return its definitions
    vector<string> searchWordInFile(const string &word) {
        ifstream file;
        string line;
        vector<string> foundDefinitions;
        try {
            file.open(filepath); // Open file in read mode
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for reading.");
            }
            while (getline(file, line)) {
                size_t pos = line.find(':'); // Find the position of the separator
                if (pos != string::npos) {
                    string fileWord = line.substr(0, pos); // Extract the word
                    string fileDefinition = line.substr(pos + 1); // Extract the definition
                    if (fileWord.find(word) != string::npos) { // Check for partial match
                        foundDefinitions.push_back(fileDefinition); // Add definition to the list
                    }
                }
            }
            file.close();
        } catch (const exception &e) {
            cerr << e.what() << endl; // Display error message
        }
        return foundDefinitions.empty() ? vector<string>{"Word not found!"} : foundDefinitions;
    }
};

// Function to display the menu options to the user
void displayMenu() {
    cout << "Dictionary Menu" << endl;
    cout << "1. Add a word" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Dictionary dict("vocabulary.txt"); // Initialize dictionary with file path
    int choice;
    string word, definition;
    vector<string> definitions;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cerr << "Invalid input. Please enter a number." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cin.ignore(); // Ignore leftover newline character
                {
                    // Check if the word already exists and display its definitions
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
                // Collect definitions from the user
                do {
                    getline(cin, definition);
                    if (definition != "done") {
                        definitions.push_back(definition);
                    }
                } while (definition != "done");
                // Add the word and definitions to the file
                dict.addWordToFile(word, definitions);
                cout << "Word added successfully!" << endl;
                definitions.clear(); // Clear definitions for next word
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                cin.ignore(); // Ignore leftover newline character
                {
                    // Search for the word and display its definitions
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
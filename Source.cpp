#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// Class to manage grocery item frequency tracking
class CornerGrocer {
private:
    map<string, int> frequencyMap;      // Stores items and their purchase counts
    string inputFilename;               // Input file name
    string outputFilename;              // Backup output file name

public:
    // Constructor to initialize file names
    CornerGrocer(const string& inputFile, const string& outputFile) {
        inputFilename = inputFile;
        outputFilename = outputFile;
    }

    // Reads items from input file and updates frequency map
    void readFile() {
        ifstream inFile(inputFilename);
        string item;

        if (!inFile) {
            cerr << "Error: Unable to open input file.\n";
            exit(1);
        }

        while (inFile >> item) {
            ++frequencyMap[item];
        }

        inFile.close();
    }

    // Writes item frequencies to backup output file
    void writeFrequencyFile() const {
        ofstream outFile(outputFilename);

        if (!outFile) {
            cerr << "Error: Unable to open output file.\n";
            exit(1);
        }

        for (const auto& pair : frequencyMap) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    // Search for a specific item and display its frequency
    void searchItemFrequency(const string& item) const {
        auto it = frequencyMap.find(item);
        if (it != frequencyMap.end()) {
            cout << item << " was purchased " << it->second << " times.\n";
        }
        else {
            cout << item << " was not found in the purchase records.\n";
        }
    }

    // Display all item frequencies
    void displayFrequencies() const {
        cout << "\nItem Purchase Frequencies:\n";
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Display item frequencies as a histogram using asterisks
    void displayHistogram() const {
        cout << "\nItem Purchase Histogram:\n";
        for (const auto& pair : frequencyMap) {
            cout << setw(12) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Prints the main menu
void printMenu() {
    cout << "\n========== Corner Grocer Menu ==========\n";
    cout << "1. Search for item frequency\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram of items\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";
}

// Validates and gets a menu option from user
int getValidatedMenuChoice() {
    int choice;
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 4: ";
        cin >> choice;
    }

    return choice;
}

// Main program driver
int main() {
    string inputFilename = "CS210_Project_Three_Input_File.txt";
    string outputFilename = "frequency.dat";

    // Create a CornerGrocer object with the input and output file names
    CornerGrocer grocer(inputFilename, outputFilename);

    // Read and store data from file, then write backup
    grocer.readFile();
    grocer.writeFrequencyFile();

    int choice;
    do {
        printMenu();
        choice = getValidatedMenuChoice();  // Ensures valid input

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item to search for: ";
            cin >> item;
            grocer.searchItemFrequency(item);
            break;
        }
        case 2:
            grocer.displayFrequencies();
            break;
        case 3:
            grocer.displayHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        }
    } while (choice != 4);

    return 0;
}

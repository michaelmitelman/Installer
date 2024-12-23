//  main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Installer.h"
#include <iostream>

using namespace std;

/// <summary>
/// Prints the correct format with an example in case of a wrong format inserted in
/// </summary>
void printUsage() {
    cerr << "Usage: Installer.exe <sourceDir> <destDir> <file1> <file2> <file3>" << endl;
    cerr << "Example: Installer.exe C:\\Source C:\\Dest file1.txt file2.txt file3.txt" << endl;
}

int main(int argc, char* argv[])
{
    // Checks if there is sufficant arguments given by the user
    if (argc != 6) {
        printUsage();
        return 1;
    }

    // Insert the arguments to the suitable places
    string sourceDir = argv[1];
    string destDir = argv[2];
    vector<string> files = { argv[3], argv[4], argv[5]};

    // Initialize a new installer
    Installer installer(sourceDir, destDir, files);

    try {
        // Launching the Installer's install function
        installer.install();
    } catch (exception& ex) {
        // Error during installation, prints error's reason
        cerr << "Error during installation: " << ex.what() << endl;
        return 1;
    }

    return 0;
}

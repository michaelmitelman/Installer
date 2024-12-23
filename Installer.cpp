#include "Installer.h"
#include "windows.h"
#include <iostream>
#include <filesystem>

using namespace std;

/// <summary>
/// Copy a single file
/// </summary>
/// <param name="fileName">file name to copy</param>
/// <returns>copy operation success/failure</returns>
bool Installer::copyFile(const string& fileName) {
	//TODO : find a path combine functionality
	wstring sourceFile = convertToWstring(m_SourceDir + "\\" + fileName);
	wstring destFile = convertToWstring(m_DestDir + "\\" + fileName);

	if (!CopyFile(sourceFile.c_str(), destFile.c_str(), FALSE)) {
		throw runtime_error("Failed to copy file: " + fileName + "\nError: " + to_string(GetLastError()) + "\n");
		return false;
	}
	return true;
}

/// <summary>
/// Create the destination folder
/// </summary>
/// <returns>directory creation success/failure</returns>
bool Installer::createDestDir() {
	wstring wideStrDestDir = convertToWstring(m_DestDir);

	// Checks if Source dir already exists
	if (isDirExists(m_DestDir)) {
		return true;
	}

	if (!CreateDirectory(wideStrDestDir.c_str(), nullptr)) {
		// The directory creation has been failed
		throw runtime_error("Failed to create directory: " + m_DestDir + "\nError: " + to_string(GetLastError()) + "\n");
		return false;
	}
	// A new directory has been created
	cout << "Creating new directory at path " << m_DestDir << endl;

	//Update member boolean value - critical to examine the cases of destination directory deletion possibility!
	m_DestDirCreated = true;
	return true;
}

/// <summary>
/// Delete a single file
/// </summary>
/// <param name="fileName">file name to be deleted</param>
void Installer::deleteFile(string fileName) {
	wstring destFile = convertToWstring(m_DestDir + "\\" + fileName);
	DeleteFile(destFile.c_str());
}

/// <summary>
/// Delete the destination folder
/// </summary>
void Installer::deleteDestDir() {
	wstring wideStrDestDir = convertToWstring(m_DestDir);
	RemoveDirectory(wideStrDestDir.c_str());
}

/// <summary>
/// Function for casting a string to a wide string
/// </summary>
/// <param name="str">a string to be converted</param>
/// <returns>wide string represents the given string</returns>
wstring Installer::convertToWstring(const string& str) {
	return wstring(str.begin(), str.end());
}

/// <summary>
/// Main operation function, launching the installation process
/// </summary>
void Installer::install() {
	try {
		// Step 1 : Check if source directory exists
		if (!isDirExists(m_SourceDir)) {
			// Source directory doesn't exists, throws an exception
			throw runtime_error("Source directory doesn't exists at path " + m_SourceDir);
		}

		// Step 2 : Create destination directory
		if (!createDestDir()) {
			// Failed to create destination directory, throws an exception
			throw runtime_error("Failed to create destination directory at path " + m_DestDir);
		}

		// Step 3 : Copy files
		for (const auto& file : m_Files) {
			cout << "Copying " << file.c_str() << ".." << endl;
			if (!copyFile(file)) {
				// Failed to copy file, throws an exception
				throw runtime_error("Failed to copy file: " + file);
			}
			cout << "Copying " << file.c_str() << " Success!" << endl;
		}

		// Print successfull copy operation message
		cout << "Copy files operation completed!" << endl;
	}
	catch (const exception& ex) {
		// Instllation failed
		cerr << "Installation failed: " << ex.what() << endl;

		cerr << "Cleanup - Deletion of copied files" << endl;
		// Delete copied files
		for (const auto& file : m_Files) {
			deleteFile(file);
		}

		// Delete destination directory - only if the directory has been created by the current process
		if (m_DestDirCreated) {
			cerr << "Cleanup - Deletion of destination file at path " << m_DestDir << endl;
			deleteDestDir();
		}
	}

}

/// <summary>
/// checks directory existence status
/// </summary>
/// <param name="filename">file's name</param>
/// <returns></returns>
bool Installer::isDirExists(const string& fileName) {
	wstring file = convertToWstring(fileName);
	// Retrieves attributes for a specified file or directory 
	DWORD fileAttributes = GetFileAttributes(file.c_str());
	// Checking if file attributes contains the flag of FILE_ATTRIBUTE_DIRECTORY
	return (fileAttributes != INVALID_FILE_ATTRIBUTES && (fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}
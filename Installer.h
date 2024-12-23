#ifndef INSTALLER_H
#define INSTALLER_H


#include <string>
#include <vector>
using namespace std;

class Installer {
	/// <summary>
	/// Represents the source directory which installer copy files from
	/// </summary>
	string m_SourceDir;

	/// <summary>
	/// Represents the destination directory which installer copy files to
	/// </summary>
	string m_DestDir;

	/// <summary>
	/// Represents the files to copy from the source directory
	/// </summary>
	vector<string> m_Files;

	/// <summary>
	/// Indicates if the destination directory has been created by the current process
	/// </summary>
	bool m_DestDirCreated = false;


public:
	// Constructor
	Installer(const string& source, const string& destination, const vector<string>& fileList)
		: m_SourceDir(source), m_DestDir(destination), m_Files(fileList) {}

	/// <summary>
	/// Main operation function, launching the installation process
	/// </summary>
	void install();

private:

	/// <summary>
	/// Copy a single file
	/// </summary>
	/// <param name="fileName">file name to copy</param>
	/// <returns>copy operation success/failure</returns>
	bool copyFile(const string& fileName);

	/// <summary>
	/// Create the destination folder
	/// </summary>
	/// <returns>directory creation success/failure</returns>
	bool createDestDir();

	/// <summary>
	/// Delete a single file
	/// </summary>
	/// <param name="fileName">file name to be deleted</param>
	void deleteFile(string fileName);

	/// <summary>
	/// Delete the destination folder
	/// </summary>
	void deleteDestDir();

	/// <summary>
	/// Function for casting a string to a wide string
	/// </summary>
	/// <param name="str">a string to be converted</param>
	/// <returns>wide string represents the given string</returns>
	wstring convertToWstring(const string& str);

	/// <summary>
	/// checks directory existence status
	/// </summary>
	/// <param name="filename">file's name</param>
	/// <returns></returns>
	bool isDirExists(const string& filename);

};

#endif // INSTALLER_H
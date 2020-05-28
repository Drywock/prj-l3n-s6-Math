#ifndef OUTPUT
#define OUTPUT

#define MAXLINES 30000

#include <fstream>
class CSVWriting {
public:
	CSVWriting();
	~CSVWriting();
	void writeToCSV(std::string content);
	void setFolderName(std::string folderName);
private:

	std::ofstream _file;
	std::string folderPath;
	int currentFileIncrement;
	int currentFileLines;
};

class logWriting {
public:
	logWriting();
	~logWriting();
	void writeToLog(std::string content);
	void setFolderName(std::string folderName);
private:
	std::ofstream _file;
	std::string folderPath;
	int currentFileIncrement;
	int currentFileLines;
};

class consoleWriting {
public:
	consoleWriting();
	~consoleWriting();
	void formatAndWrite(std::string content);
private:
};

class outputManager {
public:
	outputManager();
	~outputManager();
	void fetchData(int level, std::string content);
private:
	CSVWriting _CSVWriting;
	logWriting _logWriting;
	consoleWriting _consoleWriting;
	std::string folderPath;
};

#endif
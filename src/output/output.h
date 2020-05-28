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

class LogWriting {
public:
	LogWriting();
	~LogWriting();
	void writeToLog(std::string content);
	void setFolderName(std::string folderName);
private:
	std::ofstream _file;
	std::string folderPath;
	int currentFileIncrement;
	int currentFileLines;
};

class ConsoleWriting {
public:
	ConsoleWriting();
	~ConsoleWriting();
	void formatAndWrite(std::string content);
private:
};

class OutputManager {
public:
	OutputManager();
	~OutputManager();
	void fetchData(int level, std::string content);
private:
	CSVWriting _CSVWriting;
	LogWriting _logWriting;
	ConsoleWriting _consoleWriting;
	std::string folderPath;
};

#endif
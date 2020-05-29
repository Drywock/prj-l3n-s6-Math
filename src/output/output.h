#ifndef OUTPUT
#define OUTPUT

#define MAXLINES 20000
#define FILESTREATED 10000

#include <fstream>
class CSVWriting {
public:
	CSVWriting();
	~CSVWriting();
	void writeToCSV(const std::string& content);
	void setFolderName(const std::string& folderName);
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
	void writeToLog(const std::string& content);
	void setFolderName(const std::string& folderName);
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
	void formatAndWrite(const std::string& content);
private:
};

class OutputManager {
public:
	enum Levels
	{
		LOG_CONSOLE,
		CSV,
		CONSOLE,
		CSV_CONSOLE
	};
	OutputManager();
	~OutputManager();
	void fetchData(const Levels& level, const std::string& content);
private:
	CSVWriting _CSVWriting;
	LogWriting _logWriting;
	ConsoleWriting _consoleWriting;
	std::string folderPath;
};

#endif
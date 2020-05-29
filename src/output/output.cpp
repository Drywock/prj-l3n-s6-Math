#include <iostream>
#include <fstream>
#include <ctime>
// #include <direct.h>
#include <string>
#include "output.h"
#include "../time/time.h"

//LEVELS : 	1 is writing to log file and console
//			2 is writing to CSV only
//			3 is writing to console only
//			4 is writing to CSV and console

CSVWriting::CSVWriting() {
	CSVWriting::currentFileIncrement = 1;
	CSVWriting::currentFileLines = 0;
	CSVWriting::_file.open("");
}
CSVWriting::~CSVWriting() {}

void CSVWriting::writeToCSV(const std::string& content) {
	if (CSVWriting::currentFileLines >= MAXLINES) {
		CSVWriting::currentFileIncrement++;
		CSVWriting::currentFileLines = 0;
		CSVWriting::_file.open("./" + CSVWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".csv");
		for (size_t i = 0; i < 100; i++)
		{
			if (i > 0) {
				CSVWriting::_file << ";";
			}
			CSVWriting::_file << "u" << i;
		}
		CSVWriting::_file << "\n";
		CSVWriting::_file << content << "\n";
		CSVWriting::currentFileLines++;
		CSVWriting::_file.close();
	}
	else {
		CSVWriting::_file.open("./" + CSVWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".csv", std::ios::out | std::ios::app);
		CSVWriting::_file << content << "\n";
		CSVWriting::currentFileLines += FILESTREATED;
		CSVWriting::_file.close();
	}
	//to have 1 line with 3 cells = "case A;case B;Case C\n", separate lines with \n (dealt here) and cells with ;
}

void CSVWriting::setFolderName(const std::string& folderName)
{
	CSVWriting::folderPath = folderName;
	CSVWriting::_file.open("./" + CSVWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".csv");
	for (size_t i = 0; i < 100; i++)
	{
		if (i > 0) {
			CSVWriting::_file << ";";
		}
		CSVWriting::_file << "u" << i;
	}
	CSVWriting::_file << "\n";
	CSVWriting::_file.close();
}

LogWriting::LogWriting() {
	LogWriting::currentFileIncrement = 1;
	LogWriting::currentFileLines = 0;
	LogWriting::_file.open("");
}

LogWriting::~LogWriting() {}

void LogWriting::writeToLog(const std::string& content)
{
	if (LogWriting::currentFileLines >= MAXLINES) {
		LogWriting::_file.close();
		LogWriting::currentFileIncrement++;
		LogWriting::currentFileLines = 0;
		LogWriting::_file.open("./" + LogWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".txt");
		LogWriting::_file << "results "
			<< MAXLINES * (currentFileIncrement - 1)
			<< " to "
			<< MAXLINES * (currentFileIncrement - 1) + MAXLINES
			<< "\n";
		LogWriting::_file << content << "\n";
		LogWriting::currentFileLines++;
		LogWriting::_file.close();
	}
	else {
		LogWriting::_file.open("./" + LogWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".txt", std::ios::out | std::ios::app);
		LogWriting::_file << content << "\n";
		LogWriting::currentFileLines += FILESTREATED;
		LogWriting::_file.close();
	}
}

void LogWriting::setFolderName(const std::string& folderName)
{
	LogWriting::folderPath = folderName;
	LogWriting::_file.open("./" + LogWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".txt");
	LogWriting::_file << "results " << MAXLINES * (currentFileIncrement - 1) << " to " << MAXLINES * currentFileIncrement + MAXLINES << "\n";
}

ConsoleWriting::ConsoleWriting() {}
ConsoleWriting::~ConsoleWriting() {}

void ConsoleWriting::formatAndWrite(const std::string& content)
{
	std::cout << content << "\n";
}

OutputManager::OutputManager()
{
	std::string folderPath = "./results";
	OutputManager::_CSVWriting.setFolderName(folderPath);
	OutputManager::_logWriting.setFolderName(folderPath);
}

OutputManager::~OutputManager()
{
}

void OutputManager::fetchData(const Levels& level, const std::string& content)
{
	switch (level)
	{
	case Levels::LOG_CONSOLE:
		OutputManager::_consoleWriting.formatAndWrite(content);
		OutputManager::_logWriting.writeToLog(content);
		break;
	case Levels::CSV:
		OutputManager::_CSVWriting.writeToCSV(content);
		break;
	case Levels::CONSOLE:
		OutputManager::_consoleWriting.formatAndWrite(content);
		break;
	case Levels::CSV_CONSOLE:
		OutputManager::_consoleWriting.formatAndWrite(content);
		OutputManager::_CSVWriting.writeToCSV(content);
		break;
	default:OutputManager::_consoleWriting.formatAndWrite("Output Manager:error while fetching the data");
		break;
	}
}
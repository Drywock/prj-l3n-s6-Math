#include <iostream>
#include <fstream>
#include <ctime>
#include <direct.h>
#include <string>
#include "output.h"
#include "time/time.h"

//LEVELS : 	1 is writing to log file and console
//		2 is writing to CSV only
//		3 is writing to console only
//		4 is writing to CSV and console

CSVWriting::CSVWriting() {
	CSVWriting::currentFileIncrement = 1;
	CSVWriting::currentFileLines = 0;
	CSVWriting::_file.open("");
}
CSVWriting::~CSVWriting() {}

void CSVWriting::writeToCSV(std::string content) {
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
	}
		//to have 1 line with 3 cells = "case A;case B;Case C\n", separate lines with \n (dealt here) and cells with ;
	CSVWriting::_file<<content<<"\n";
}

void CSVWriting::setFolderName(std::string folderName)
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
}

logWriting::logWriting() {
	logWriting::currentFileIncrement = 1;
	logWriting::currentFileLines = 0;
	logWriting::_file.open("");
}

logWriting::~logWriting() {}

void logWriting::writeToLog(std::string content)
{
	if (logWriting::currentFileLines >= MAXLINES) {
		logWriting::_file.close();
		logWriting::currentFileIncrement++;
		logWriting::currentFileLines = 0;
		logWriting::_file.open("./" + logWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".txt");
		logWriting::_file << "results " 
				  << MAXLINES * (currentFileIncrement - 1) 
				  << " to " 
				  << MAXLINES * currentFileIncrement + MAXLINES 
				  << "\n";
	}
	logWriting::_file << content << "\n";
}

void logWriting::setFolderName(std::string folderName)
{
	logWriting::folderPath = folderName;
	logWriting::_file.open("./" + logWriting::folderPath + "/" + std::to_string(currentFileIncrement) + ".txt");
	logWriting::_file << "results " << MAXLINES * (currentFileIncrement - 1) << " to " << MAXLINES * currentFileIncrement + MAXLINES << "\n";
}

consoleWriting::consoleWriting() {}
consoleWriting::~consoleWriting() {}

void consoleWriting::formatAndWrite(std::string content)
{
	std::cout << content << "\n";
}

outputManager::outputManager()
{
	//attempt to have unique names for every run
	/*time_t currentTime = time(0);
	std::cout << ctime(&currentTime);
	std::string folderPath = "../\"";
	folderPath = folderPath + ctime(&currentTime) + "\"";
	if (mkdir(folderPath.c_str()) == 0) {
		std::cout << folderPath.c_str();
	}
	else {
		std::cout << "naah";
	}*/
	std::string folderPath = "./results";
	if (mkdir(folderPath.c_str()) == 0) {
		//directory created
	}
	else {
		//directory already exists
	}
	outputManager::_CSVWriting.setFolderName(folderPath);
	outputManager::_logWriting.setFolderName(folderPath);
}

outputManager::~outputManager()
{
}

void outputManager::fetchData(int level, std::string content)
{
	switch (level)
	{
	case 1:
		outputManager::_consoleWriting.formatAndWrite(content);
		outputManager::_logWriting.writeToLog(content);
		break;
	case 2:
		outputManager::_CSVWriting.writeToCSV(content);
		break;
	case 3:
		outputManager::_consoleWriting.formatAndWrite(content);
		break;
	case 3:
		outputManager::_consoleWriting.formatAndWrite(content);
		outputManager::_CSVWriting.writeToCSV(content);
		break;
	default:outputManager::_consoleWriting.formatAndWrite("Output Manager:error while fetching the data");
		break;
	}
}

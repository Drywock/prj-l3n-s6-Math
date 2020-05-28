#ifndef OUTPUT
#define OUTPUT

#define MAXLINES 30000

#include <fstream>
class CSVWriting{
public:
    CSVWriting();
    ~CSVWriting();
    void writeToCSV(std::string content);
private:

    std::ofstream _file;
    int currentFileIncrement;
    int currentFileLines;
};

class logWriting{
public:
    logWriting();
    ~logWriting();
private:
    int currentFileIncrement;
    int currentFileLines;
};

class consoleWriting{
public:
    consoleWriting();
    ~consoleWriting();
    void formatAndWrite(std::string content){

    }
private:

};

class outputManager{
public:
    outputManager();
    ~outputManager();
    void initialize();
private:
    CSVWriting _CSVWriting;
    logWriting _logWriting;
    consoleWriting _consoleWriting;
};

#endif
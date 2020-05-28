#include <iostream>
#include <fstream>
#include <ctime>
#include <direct.h>
#include "output.h"

CSVWriting::CSVWriting(){
    CSVWriting::currentFileIncrement=1;
    CSVWriting::currentFileLines=0;
    CSVWriting::_file.open("");
}
void CSVWriting::writeToCSV(std::string content){
    if(CSVWriting::currentFileLines>=MAXLINES){
        CSVWriting::currentFileIncrement++;
        CSVWriting::currentFileLines=0;
        CSVWriting::_file.open("");
    }
    else if(CSVWriting::currentFileIncrement==0){
        
    }
}

void outputManager::initialize(){
    time_t mytime=time(0);
    std::cout<<ctime(&mytime);
    //mkdir()
    outputManager::_consoleWriting;
    outputManager::_CSVWriting;
    outputManager::_logWriting;

}

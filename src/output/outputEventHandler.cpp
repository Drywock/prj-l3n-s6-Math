#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
//#include <mutex>
#include "outputEventHandler.h"
#include "time.h"

outputEventHandler::outputEventHandler(int threadAmount){
        outputEventHandler::_Buffer;
}

outputEventHandler::~outputEventHandler(){
    
}

void outputEventHandler::writeDataToBuffer(int threadID,int level,std::string content){
    //lock the access
    //outputEventHandler::_Buffer.lock.lock();

    outputEventHandler::_Buffer.lines.push(content);
    outputEventHandler::_Buffer.level.push(level);
    outputEventHandler::_Buffer.has_been_modified=true;
    //unlock the access
    //outputEventHandler::_Buffer.lock.unlock();    
}

Data outputEventHandler::readDateFromBuffer(){
    //lock the access
    //outputEventHandler::_Buffer.lock.lock();

    std::string content=outputEventHandler::_Buffer.lines.front();
    outputEventHandler::_Buffer.lines.pop();
    int level=outputEventHandler::_Buffer.level.front();
    outputEventHandler::_Buffer.level.pop();
    //unlock the access
    //outputEventHandler::_Buffer.lock.unlock();  
    return {content, level};
}
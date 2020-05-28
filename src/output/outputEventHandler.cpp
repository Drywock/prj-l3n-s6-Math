#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <mutex>
#include <thread>
#include "outputEventHandler.h"
#include "../time/time.h"
#include "output.h"

void OutputEventHandler::start(){
	std::thread t(&OutputEventHandler::worker);
}

void OutputEventHandler::writeDataToBuffer(int level, std::string content) {
	//lock the access
	OutputEventHandler::_Buffer.lock.lock();

	OutputEventHandler::_Buffer.lines.push(content);
	OutputEventHandler::_Buffer.level.push(level);
	OutputEventHandler::_Buffer.has_been_modified = true;
	//unlock the access
	OutputEventHandler::_Buffer.lock.unlock();
}

Data OutputEventHandler::readDateFromBuffer() {
	//lock the access
	OutputEventHandler::_Buffer.lock.lock();

	std::string content = OutputEventHandler::_Buffer.lines.front();
	OutputEventHandler::_Buffer.lines.pop();
	int level = OutputEventHandler::_Buffer.level.front();
	OutputEventHandler::_Buffer.level.pop();
	//unlock the access
	OutputEventHandler::_Buffer.lock.unlock();
	return { content, level };
}
	

void OutputEventHandler::worker(){
	do{
		if(OutputEventHandler::_Buffer.has_been_modified){
			Data data = readDateFromBuffer();
			OutputEventHandler::_manager.fetchData(data.level, data.content);
		}
	}while(1);
}
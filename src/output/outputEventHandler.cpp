#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <mutex>
#include "outputEventHandler.h"
#include "../time/time.h"
#include "output.h"

OutputEventHandler::OutputEventHandler() {
	OutputEventHandler::_Buffer;
}

OutputEventHandler::~OutputEventHandler() {
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
//TODO
void OutputEventHandler::catchEventBufferModified() {
	Data data = readDateFromBuffer();
	OutputEventHandler::_manager.fetchData(data.level, data.content);
}
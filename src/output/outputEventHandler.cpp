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

Buffer OutputEventHandler::_Buffer;
OutputManager OutputEventHandler::_manager;
bool OutputEventHandler::_stop = false;

void OutputEventHandler::writeDataToBuffer(const OutputManager::Levels& level, const std::string& content) {
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
	OutputManager::Levels level = OutputEventHandler::_Buffer.level.front();
	OutputEventHandler::_Buffer.level.pop();
	if (OutputEventHandler::_Buffer.level.empty() && OutputEventHandler::_Buffer.lines.empty()) {
		OutputEventHandler::_Buffer.has_been_modified = false;
	}
	//unlock the access
	OutputEventHandler::_Buffer.lock.unlock();
	return { content, level };
}

void OutputEventHandler::worker() {
	OutputEventHandler::_stop = false;
	do {
		if (OutputEventHandler::_Buffer.has_been_modified && (OutputEventHandler::_Buffer.lines.size() > FILESTREATED || OutputEventHandler::_stop)) {
			Data data;
			for (size_t i = 0; i < FILESTREATED; i++)
			{
				Data temp = readDateFromBuffer();

				data.level = temp.level;
				data.content += temp.content;
				if (i < (FILESTREATED - 1)) {
					data.content += "\n";
				}
			}
			OutputEventHandler::_manager.fetchData(data.level, data.content);
		}
	} while (!(OutputEventHandler::_stop) && OutputEventHandler::_Buffer.has_been_modified);
}

void OutputEventHandler::stopWorker() {
	while (OutputEventHandler::_Buffer.has_been_modified)
	{
	}
	OutputEventHandler::_stop = true;
}
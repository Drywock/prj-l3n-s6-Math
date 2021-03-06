#ifndef OUTPUTEVENTHANDLER
#define OUTPUTEVENTHANDLER

#include <mutex>
#include <vector>
#include <queue>
#include "output.h"

class SLock
{
public:
	void lock()
	{
		lck.lock();
	}

	void unlock()
	{
		lck.unlock();
	}

private:
	std::mutex lck;
};

struct Buffer {
	std::queue<std::string> lines;
	std::queue<OutputManager::Levels> level;
	bool isNotEmpty;
	SLock lock;
	Buffer() {
		isNotEmpty = false;
	}
};

struct Data {
	std::string content;
	OutputManager::Levels level;
};

class OutputEventHandler {
public:
	static void worker();
	static void writeDataToBuffer(const OutputManager::Levels& level, const std::string& content);
	static Data readDateFromBuffer();
	static void stopWorker();
    static void initFolder(const std::string &path = "./results");
private:
	static bool _stop;
	static Buffer _Buffer;
	static OutputManager *_manager;
};

#endif
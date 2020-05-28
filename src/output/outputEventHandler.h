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
	std::queue<int> level;
	int position;
	int readPosition;
	bool has_been_modified;
	SLock lock;
};

struct Data {
	std::string content;
	int level;
};

class OutputEventHandler {
public:
	static void start();
	static void writeDataToBuffer(int level, std::string content);
	static Data readDateFromBuffer();

private:
	static void worker();
	static Buffer _Buffer;
	static OutputManager _manager;
};

#endif
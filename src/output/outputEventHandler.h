#ifndef OUTPUTEVENTHANDLER
#define OUTPUTEVENTHANDLER

//#include <mutex>
#include <vector>
#include "output.h"

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

class OutputEventHandler {
public:
	OutputEventHandler();
	~OutputEventHandler();

	void writeDataToBuffer(int level, std::string content);
	Data readDateFromBuffer();

	//TODO
	void catchEventBufferModified();
private:
	Buffer _Buffer;
	OutputManager _manager;
};

#endif
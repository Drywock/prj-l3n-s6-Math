#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "time/time.h"
#include "output/outputEventHandler.h"
#include "output/output.h"
#include "f.h"

#define START 2
#define MAX_N 100000000

int main() {
	uint64_t start = 0;
	uint64_t max_n = 0;
	std::cout << "star value : ";
	std::cin >> start;
	std::cout << "max value : ";
	std::cin >> max_n;
	TIME_INIT_SESSION("Global timing");
	{
		TIME(main);
		/*
		OutputEventHandler out;
		out.writeDataToBuffer(3, "test");
		*/
		std::thread t(OutputEventHandler::worker);
		for (uint64_t n = start; n <= max_n; n++) {
			std::vector<uint64_t> uns;
			uint64_t result = n;
			uint64_t oldResult = 0;

			while (result != oldResult)
			{
				oldResult = result;
				result = f_rho_Pollard(oldResult);
				uns.push_back(result);
			}

			std::stringstream result_str;
			result_str << n;
			for (auto un : uns) {
				result_str << ";" << un;
			}
			OutputEventHandler::writeDataToBuffer(OutputManager::Levels::CSV, result_str.str());
		}
		std::cout << "finished calculating\n";

		OutputEventHandler::stopWorker();
		t.join();
	}
	TIME_END_SESSION;
	return 0;
}
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "time/time.h"
#include "output/outputEventHandler.h"
#include "output/output.h"
#include "f.h"

int main() {
	uint64_t start = 0;
	uint64_t max_n = 0;
    int response;
	std::cout << "star value : ";
	std::cin >> start;
	std::cout << "max value : ";
	std::cin >> max_n;
    std::stringstream resultPath;
    resultPath << "./results_from_" << start << "_to_" << max_n;

	TIME_INIT_SESSION("Global timing");
	{
        uint64_t n;
        const uint64_t span = max_n - start;
        int progress = 1; 

		TIME(main);
        std::cout << "In progess 0%\n";
        try{
            OutputEventHandler::initFolder(resultPath.str());
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

                if(n >= progress * span / 100) {
                    std::cout << "in progress " << progress <<"%\n";
                    progress++;
                }
            }
            std::cout << "finished calculating\n";

            OutputEventHandler::stopWorker();
            t.join();
        } catch(std::exception e) {
            std::cout << "ERROR: " << e.what() << "\nLast n: " << n << "\n";
        }
	}
	TIME_END_SESSION;
	return 0;
}
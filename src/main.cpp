#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "time/time.h"
#include "output/outputEventHandler.h"
#include "output/output.h"
#include "f.h"

#define MAX_N 1000000

int main() {
	TIME_INIT_SESSION("Global timing");
	
    {   
        TIME(main);
        std::thread t(OutputEventHandler::worker);
        for (uint64_t n = 2; n <= MAX_N; n++) {
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
            OutputEventHandler::writeDataToBuffer(OutputManager::Levels::LOG_CONSOLE, result_str.str());
        }
        OutputEventHandler::stopWorker();
        t.join();
    }
	TIME_END_SESSION;
}
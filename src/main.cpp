#include <iostream>
#include <string>
#include <sstream>
#include "time/time.h"
#include "output/outputEventHandler.h"
#include "f.h"

#define MAX_N 100

int main() {
    TIME_INIT_SESSION("Global timing");
    OutputEventHandler out;

    for(uint64_t n = 2; n < MAX_N; n++) {
        std::vector<uint64_t> uns;
        uint64_t result = n;
        do
        {
            result = f_rho_Pollard(result);
            uns.push_back(result);
        } while (result != n);


        std::stringstream result_str;
        result_str << n;
        for(auto un : uns) {
            result_str << ";" << un;
        }

        out.writeDataToBuffer(4, result_str.str());
    }
    TIME_END_SESSION;
}
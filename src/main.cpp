#include <iostream>
#include <string>
#include "time/time.h"
#include "f.h"

#define MAX_N 100

int main() {
    TIME_INIT_SESSION("Global timing");
    for(uint64_t n = 2; n < MAX_N; n++) {
        std::vector<uint64_t> uns=();
        uint64_t result = n;
        do
        {
            result = f_rho_Pollard(result);
            un.push_back(result);
        } while (result != n);


        std::string result_str(n);
        for(auto un : uns) {
            result_str += std::string(un);
        }
        

    }
    TIME_END_SESSION;
}
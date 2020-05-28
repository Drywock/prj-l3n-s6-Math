#include <iostream>
#include "time/time.h"
#include "f.h"

#define MAX_N 100

int main() {
    TIME_INIT_SESSION("Global timing");
    for(uint64_t n = 2; n < MAX_N; n++) {
        std::vector<uint64_t> un;
        uint64_t result = n;
        do
        {
            result = f_rho_Pollard(result);
            un.push_back(result);
        } while (result != n);
        
    }
    TIME_END_SESSION;
}
#include "f.h"

#include <map>
#include <iostream>

#include "functions.h"
#include "rhoPollard.h"
#include "time/time.h"

std::map<uint64_t, uint64_t> *g_results = new std::map<uint64_t, uint64_t>;

uint64_t f_rho_Pollard(const uint64_t &n) {
    TIME(f_rho_Pollard);
    int64_t result;
    
    if(g_results->count(n)) {
        return (*g_results)[n];
    }

    RhoPollard r;
    std::vector<uint64_t> factors = r.getFactors(n);
    result = sumAllCombination(factors);
    (*g_results)[n] = result;
    return result;
}
#include "f.h"

#include <map>

#include "functions.h"
#include "rhoPollard.h"

uint64_t f_rho_Pollard(const uint64_t &n) {
    static std::map<uint64_t, uint64_t> results;
    try {
        return results.at(n);
    } catch(std::out_of_range e) {
        rhoPollard r;
        int64_t result = sumAllCombination(r.getFactors(n));
        results.insert(std::pair<uint64_t, uint64_t>(n, result));
        return result;
    }
}
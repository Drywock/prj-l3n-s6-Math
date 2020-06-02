#include "functions.h"

#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include "time/time.h"

uint64_t power(const uint64_t &n, const uint64_t &exp) {
    if(n == 0) return 1;
    uint64_t res = n;
    for(uint64_t i = 1; i < exp; i++) {
        res *= n;
    }
    return res;
}

uint64_t sumAllCombination(const std::vector<uint64_t>& primaryDecompostion)
{
	TIME(Sum_all_dividers);
	uint64_t n = 1;
	uint64_t sum = 1;
    
    std::map<uint64_t, uint64_t> primFactors({});
    for (auto div : primaryDecompostion) {
        if(primFactors.count(div) == 0){
            primFactors[div] = 1;
            }
        else{
            primFactors[div]++;
        }
    }

    uint64_t a, b, tot;
	for (auto primFactor : primFactors)
	{
        a = power(primFactor.first, primFactor.second + 1) - 1;
        b =  primFactor.first - 1;
        tot = a / b;
		sum *= tot;
	}
    
	return sum;
}

bool isPrime(uint64_t n) {
	uint64_t max = std::sqrt(n);
	for (uint64_t i = 2; i <= max; i++) {
		if ((n % i) == 0) {
			return false;
		}
	}
	return true;
}

uint64_t gcd(uint64_t a, uint64_t b)
{
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

uint64_t absoluteDiff(uint64_t a, uint64_t b) {
	if (a >= b) {
		return a - b;
	}
	else {
		return b - a;
	}
}
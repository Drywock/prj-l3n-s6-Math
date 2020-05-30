#include "f.h"

#include <map>
#include <iostream>

#include "functions.h"
#include "rhoPollard.h"
#include "time/time.h"

std::map<uint64_t, uint64_t>* g_results = new std::map<uint64_t, uint64_t>;

uint64_t f_rho_Pollard(const uint64_t& n) {
	//TIME(f_rho_Pollard);
	int64_t result = 0;

	if (g_results->count(n)) {
		return (*g_results)[n];
	}

	RhoPollard r;
	r.factorize(n);
	uint64_t factors = r.getFactors();
	/*for (int i = 0; i != factors.size(); ++i)
	{
		result += factors[i];
	}*/
	//result = sumAllCombination(factors);
	//result += n;
	(*g_results)[n] = factors;
	return factors;
}
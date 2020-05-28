#include "functions.h"

#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include "time/time.h"

void calcDividers(std::set<uint64_t>& dividers, const std::vector<uint64_t>& availbleValues, const size_t& depth, const uint64_t& value = 1);

uint64_t sumAllCombination(const std::vector<uint64_t>& primaryDecompostion)
{
	//TIME(Sum_all_dividers);
	uint64_t n = 1;
	uint64_t sum = 0;
	std::set<uint64_t> dividers;

	calcDividers(dividers, primaryDecompostion, primaryDecompostion.size());

	for (auto divider : dividers)
	{
		sum += divider;
	}

	return sum;
}

void calcDividers(std::set<uint64_t>& dividers, const std::vector<uint64_t>& availbleValues, const size_t& depth, const uint64_t& value) {
	if (depth <= 0) return;

	for (auto element : availbleValues) {
		uint64_t newValue = value * element;

		std::vector<uint64_t> newAvailableValues(availbleValues);
		auto index = std::find(newAvailableValues.begin(), newAvailableValues.end(), element);
		newAvailableValues.erase(index);

		dividers.insert(newValue);
		calcDividers(dividers, newAvailableValues, depth - 1, newValue);
	}
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
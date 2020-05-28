#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include "functions.h"
#include "time/time.h"

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

bool absolute(uint64_t a){
	return (a>0)?a:-a;
}
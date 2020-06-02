#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rhoPollard.h"
#include "functions.h"
#include "time/time.h"

uint64_t RhoPollard::getDivisor(const uint64_t& n) {
	uint64_t x = std::rand() % n + 1;
	uint64_t y = x;
	uint64_t g = 1;
	//fn is f(x) = x*x + random between 0 and n+1
	while (g == 1)
	{
		x = ((x * x) + std::rand() % (n + 1)) % (n);
		y = ((y * y) + std::rand() % (n + 1));
		y = ((y * y) + std::rand() % (n + 1)) % (n);
		g = gcd(absoluteDiff(x, y), n);
	}
	return g;
}

void RhoPollard::factorize(const uint64_t& n)
{
	//std::cout<<"factorization of "<<n<<" ";

	if (n == 1) {
		return;
	}

	if (isPrime(n))
	{
        RhoPollard::factors.push_back(n);
		return;
	}

	uint64_t divisor;
	divisor = RhoPollard::getDivisor(n);
	RhoPollard::factorize(divisor);
	RhoPollard::factorize(n / divisor);
}

void RhoPollard::showFactors() {
	for (int i = 0; i != RhoPollard::factors.size(); ++i)
	{
		std::cout << RhoPollard::factors[i] << " ";
	}
}

std::vector<uint64_t> RhoPollard::getFactors(const uint64_t& n) {
	RhoPollard::factors.clear();
	RhoPollard::factorize(n);
	return RhoPollard::factors;
}
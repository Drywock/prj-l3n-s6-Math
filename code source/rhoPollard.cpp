#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rhoPollard.h"
#include "functions.h"
#include "time/time.h"

uint64_t RhoPollard::getDivisor(const uint64_t& n) {
	/*if (n % 2 == 0) {
		return 2;
	}*/
	uint64_t x = 2;
	uint64_t y = x;
	uint64_t g = 1;
	//fn is f(x) = x*x + random between 0 and n+1
	//std::cout << "test\n";
	do
	{
		x = ((x * x) + std::rand()) % (n + 1);
		y = ((y * y) + std::rand()) % (n + 1);
		y = ((y * y) + std::rand()) % (n + 1);
		g = gcd(absoluteDiff(x, y), n);
		if (g > 1) {
			return g;
		}
	} while (x != y);
	return RhoPollard::getDivisor(n);
}

void RhoPollard::factorize(const uint64_t& n)
{
	if (n == 1) {
		return;
	}
	//std::cout << "adding factor " << n << "\n";
	if (n % 2 == 0 && n / 2 != 1) {
		if (!std::count(RhoPollard::factors.begin(), RhoPollard::factors.end(), n / 2)) {
			RhoPollard::factors.push_back(n / 2);
		}
	}

	if (!std::count(RhoPollard::factors.begin(), RhoPollard::factors.end(), n)) {
		RhoPollard::factors.push_back(n);
	}
	if (isPrime(n))
	{
		return;
	}

	uint64_t divisor;
	divisor = RhoPollard::getDivisor(n);
	RhoPollard::factorize(divisor);
	RhoPollard::factorize(n / divisor);
}

uint64_t RhoPollard::showFactors() {
	uint64_t sum = 0;
	for (int i = 0; i != RhoPollard::factors.size(); ++i)
	{
		sum += RhoPollard::factors[i];
	}
	std::cout << sum << "\n";
	return sum;
}

uint64_t RhoPollard::getFactors() {
	//RhoPollard::factors.clear();
	uint64_t sum = 0;
	//RhoPollard::factorize(n);

	for (int i = 0; i != RhoPollard::factors.size(); ++i)
	{
		sum += RhoPollard::factors[i];
	}
	return sum;
}
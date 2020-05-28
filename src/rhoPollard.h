#ifndef RHOPOLLARD
#define RHOPOLLARD

#include <vector>

class RhoPollard
{
public:

	std::vector<uint64_t> getFactors(const uint64_t &n);

private:
	void factorize(const uint64_t &n);
	uint64_t getDivisor(const uint64_t &n);
	void showFactors();
	std::vector<uint64_t> factors;
};

#endif
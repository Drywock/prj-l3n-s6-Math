#ifndef RHOPOLLARD
#define RHOPOLLARD

#include <vector>

class RhoPollard
{
public:

	uint64_t getFactors();
	void factorize(const uint64_t& n);
	uint64_t showFactors();
private:

	uint64_t getDivisor(const uint64_t& n);
	std::vector<uint64_t> factors;
};

#endif
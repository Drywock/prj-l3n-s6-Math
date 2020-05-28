#ifndef RHOPOLLARD
#define RHOPOLLARD

#include <vector>

class rhoPollard
{
public:

	std::vector<int> getFactors(int n);

private:
	void factorize(int n);
	int getDivisor(int n);
	void showFactors();
	std::vector<int> factors;
};

#endif
#ifndef _RAND_NUM_H
#define _RAND_NUM_H

#include <random>

class RandNum
{
public:
	static RandNum& Instance();

	double GetRandNum();
private:
	RandNum();

	RandNum(const RandNum&) = delete;
	void operator=(const RandNum&) = delete;

	std::mt19937 mt;
	std::random_device rd;
	std::uniform_real_distribution<double> dist;
};

#endif
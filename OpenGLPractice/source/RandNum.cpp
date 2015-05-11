#include "RandNum.h"

RandNum::RandNum()
	: mt(rd()),
	dist(0, 1)
{

}

RandNum& RandNum::Instance()
{
	static RandNum instance;
	return instance;
}

double RandNum::GetRandNum()
{
	return dist(mt);
}

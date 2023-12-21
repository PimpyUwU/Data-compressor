#include "Letter.h"

Letter::Letter(unsigned char code, unsigned int frequency)
{
	this->frequency = frequency;
	this->code = code;
}

unsigned int Letter::getFrequency()
{
	return frequency;
}

unsigned char Letter::getCode()
{
	return code;
}

void Letter::setCode(unsigned char code)
{
	this->code = code;
}

void Letter::setFrequency(unsigned int frequency)
{
	this->frequency = frequency;
}



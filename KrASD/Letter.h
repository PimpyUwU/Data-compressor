#pragma once
class Letter
{
public:
	Letter(unsigned char code, unsigned int frequency);
	unsigned int getFrequency();
	unsigned char getCode();
	void setCode(unsigned char code);
	void setFrequency(unsigned int frequency);

private:
	unsigned char code;
	unsigned int frequency;
};


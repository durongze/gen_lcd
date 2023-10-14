#ifndef __LCD_PIX__
#define __LCD_PIX__

#include <iostream>

class LcdPix
{
public:
	LcdPix(size_t bitWidth = 0);
	~LcdPix();
	size_t GetBit(size_t idx);
	size_t GetVal();
	void SetVal(size_t val);
	void Dump(std::ostream& os) const;
private:
	size_t m_bitWidth;
	size_t m_val;
};

#endif

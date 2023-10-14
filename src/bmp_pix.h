#ifndef __BMP_PIX__
#define __BMP_PIX__

#include <iostream>
#include "bmp_file.h"

class BmpPix
{
public:
	BmpPix(size_t bitWidth = 8);
	~BmpPix();
	size_t GetBitWidth() const;
	void SetBitWidth(size_t bitWidth);
	size_t GetBit(size_t idx);
	size_t GetVal();
	void SetVal(size_t val);
	void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& bmpFile, BmpPix& bmpCtx);
    friend std::ostream& operator<<(std::ostream& bmpFile, BmpPix& bmpCtx);
private:
	size_t m_bitWidth;
	size_t m_val;
};

#endif
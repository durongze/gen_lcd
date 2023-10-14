#ifndef __BMP_CTX__
#define __BMP_CTX__

#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_pix.h"
#include "lcd_ctx.h"

class BmpPix;
class LcdCtx;

class BmpCtx
{
public:
	BmpCtx(size_t width, size_t height, size_t pixWidth);
	~BmpCtx();
	void SetBitWidth(size_t pixWidth);
	size_t GetBitWidth() const;
	void Resize(size_t width, size_t heigth);
	void SetVal(size_t width, size_t height, size_t val);
	int ToLcdCtx(LcdCtx &lcdCtx);
	void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream &bmpFile, BmpCtx &bmpCtx);
private:
	size_t m_width;
	size_t m_height;
	size_t m_pixWidth;
	std::vector<BmpPix> m_ctx;
};

#endif
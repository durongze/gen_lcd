
#ifndef __LCD_CTX__
#define __LCD_CTX__

#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_ctx.h"
#include "lcd_pix.h"

class BmpCtx;
class LcdPix;

class LcdCtx
{
public:
	LcdCtx(size_t width, size_t height, size_t pixWidth);
	~LcdCtx();
	void Resize(size_t width, size_t heigth);
	void SetVal(size_t width, size_t height, size_t val);
	int ToBmpCtx(BmpCtx& bmpCtx);
	void Dump(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& bmpFile, LcdCtx& bmpCtx);
private:
	size_t m_width;
	size_t m_height;
	size_t m_pixWidth;
	std::vector<LcdPix> m_ctx;
};

#endif
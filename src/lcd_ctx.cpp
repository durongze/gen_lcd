#include "lcd_ctx.h"

LcdCtx::LcdCtx(size_t width, size_t height, size_t pixWidth) : m_width(width), m_height(height), m_pixWidth(pixWidth), m_ctx(m_width* m_height, LcdPix(pixWidth)) {
}
LcdCtx::~LcdCtx() {}

void LcdCtx::Resize(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
	m_ctx.resize(m_height * m_width);
}

void LcdCtx::SetVal(size_t width, size_t height, size_t val)
{
	m_ctx[height * m_width + width].SetVal(val);
}

int LcdCtx::ToBmpCtx(BmpCtx& bmpCtx)
{
	unsigned char pix;
	size_t line_h = 8;
	size_t w, h, d;
	bmpCtx.Resize(m_width, m_height);
	for (h = 0; h < m_height; h += line_h) {
		for (w = 0; w < m_width; w++) {
			pix = 0;
			for (d = 0; d < line_h; d++) {
				pix |= m_ctx[m_width * d + w].GetBit(d) << (m_height - d);
			}
			bmpCtx.SetVal(w, h, pix);
		}
	}
	return 0;
}

std::ostream& operator<<(std::ostream& bmpFile, LcdCtx& bmpCtx)
{
	return bmpFile;
}

void LcdCtx::Dump(std::ostream& os) const
{
	os << std::dec << "LcdCtx width:" << m_width << ", height:" << m_height << ", bitWidth:" << m_pixWidth << std::hex << std::endl;
	size_t w, h;
	for (h = 0; h < m_height; h++) {
		os << "LcdCtx[" << std::dec << h << std::hex << "]:" << std::endl;
		for (w = 0; w < m_width; w++) {
			m_ctx[h * m_width + w].Dump(os);
		}
		os << std::endl;
	}
}
#include "bmp_ctx.h"


BmpCtx::BmpCtx(size_t width, size_t height, size_t pixWidth) : m_width(width), m_height(height), m_pixWidth(pixWidth),m_ctx(m_width* m_height, BmpPix(pixWidth)) {
}
BmpCtx::~BmpCtx() {}

void BmpCtx::SetBitWidth(size_t pixWidth)
{
	m_pixWidth = pixWidth;
}

size_t BmpCtx::GetBitWidth() const
{
	return m_pixWidth;
}

void BmpCtx::Resize(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
	m_ctx.resize(m_height * m_width);
}

void BmpCtx::SetVal(size_t width, size_t height, size_t val)
{
	m_ctx[height * m_width + width].SetVal(val);
}

int BmpCtx::ToLcdCtx(LcdCtx& lcdCtx)
{
	unsigned char pix;
	size_t w, h, d;
	size_t line_h = 8;
	size_t bitWidth = 0;
	lcdCtx.Resize(m_width, m_height);
	for (h = 0; h < m_height; h += line_h) {
		for (w = 0; w < m_width; w++) {
			pix = 0;
			for (d = 0; d < line_h; d++) {
				// pix = m_ctx[m_width * d + w].GetBit(d) << (m_height - d);
				bitWidth = m_ctx[m_width * d + w].GetBitWidth();
				switch (bitWidth) {
				case 8:
					pix = m_ctx[m_width * d + w].GetBit(d) << (line_h - d);
					break;
				case 16:
					pix = m_ctx[m_width * d + w].GetBit(d) << (line_h - d);
					break;
				case 24:
					pix = m_ctx[m_width * d + w].GetBit(d) << (line_h - d);
					break;
				default:
					pix = m_ctx[m_width * d + w].GetBit(d) << (line_h - d);
					break;
				}
			}
			lcdCtx.SetVal(w, h, pix);
		}
	}
	return 0;
}

void BmpCtx::Dump(std::ostream& os) const
{
	os << "BmpCtx width:" << std::dec << m_width << ", height:" << m_height << ", bitWidth:" << m_pixWidth << std::hex << std::endl;
	size_t w, h;
	for (h = 0; h < m_height; h++) {
        os << "BmpCtx[" << std::dec << h << std::hex << "]:" << std::endl;		
		for (w = 0; w < m_width; w++) {
			m_ctx[h * m_width + w].Dump(os);
		}
		os << std::endl;
	}
}

std::istream& operator>>(std::istream & bmpFile, BmpCtx& bmpCtx)
{
	size_t w, h;

	for (h = 0; h < bmpCtx.m_height; h++) {
		for (w = 0; w < bmpCtx.m_width; w++) {
			bmpCtx.m_ctx[h * bmpCtx.m_width + w].SetBitWidth(bmpCtx.GetBitWidth());
			bmpFile >> bmpCtx.m_ctx[h * bmpCtx.m_width + w];
			std::cout <<  bmpCtx.m_ctx[h * bmpCtx.m_width + w] << std::endl;
		}
	}
	return bmpFile;
}
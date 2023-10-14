#include "lcd_pix.h"

LcdPix::LcdPix(size_t bitWidth) :m_bitWidth(bitWidth), m_val(0) {
}
LcdPix::~LcdPix() {}

size_t LcdPix::GetBit(size_t idx)
{
	return (m_val & (1 << idx)) >> idx;
}

size_t LcdPix::GetVal()
{
	return m_val;
}

void LcdPix::SetVal(size_t pix)
{
	m_val = pix;
}

void LcdPix::Dump(std::ostream& os) const
{
	os << "[" << std::hex << m_val << "]";
}
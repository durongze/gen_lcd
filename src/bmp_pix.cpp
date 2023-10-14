#include "bmp_pix.h"

BmpPix::BmpPix(size_t bitWidth) :m_bitWidth(bitWidth), m_val(0) {}

BmpPix::~BmpPix() {}

size_t BmpPix::GetBitWidth() const
{
	return m_bitWidth;
}

void BmpPix::SetBitWidth(size_t bitWidth)
{
	m_bitWidth = bitWidth;
}

size_t BmpPix::GetBit(size_t idx)
{
	return (m_val & (1 << idx)) >> idx;
}

size_t BmpPix::GetVal()
{
	return m_val;
}

void BmpPix::SetVal(size_t pix)
{
	m_val = pix;
}

void BmpPix::Dump(std::ostream& os) const
{
	os << "[" << std::hex << m_val << "]";
}

std::istream& operator>>(std::istream& bmpFile, BmpPix& bmpPix)
{
	unsigned char val = 0;
	switch (bmpPix.m_bitWidth) {
	case 8: {
		bmpFile >> val;
		bmpPix.m_val = val;
		break;
	}
	case 16: {
		bmpFile >> val;
		bmpPix.m_val = (size_t)(val) << 11;
		bmpFile >> val;
		bmpPix.m_val |= (size_t)(val) << 5;
		bmpFile >> val;
		bmpPix.m_val |= val;
		break;
	}
	case 24: {
		bmpFile >> val;
		bmpPix.m_val = (size_t)(val) << 16;
		bmpFile >> val;
		bmpPix.m_val |= (size_t)(val) << 8;
		bmpFile >> val;
		bmpPix.m_val |= val;
		break;
	}
	default:
		break;
	}
	return bmpFile;
}

std::ostream& operator<<(std::ostream& bmpFile, BmpPix& bmpPix)
{
	unsigned char val = 0;
	switch (bmpPix.m_bitWidth) {
	case 8: {
		val = bmpPix.m_val;
		bmpFile << val;
		break;
	}
	case 16: {
		val = bmpPix.m_val;
		bmpFile << val;
		break;
	}
	case 24: {
		val = bmpPix.m_val;
		bmpFile << val;
		break;
	}
	default:
		break;
	}
	return bmpFile;
}
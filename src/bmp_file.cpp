#include "bmp_file.h"

struct BmpFileHeader {
	char bfType[2];
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
	friend std::istream& operator>>(std::istream& bmpFile, BmpFileHeader& bmpCtx);
};

struct BmpInfoHeader {
	unsigned int biSize;
	long biWidth;
	long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	long biXpelsPerMeter;
	long biYpelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
	friend std::istream& operator>>(std::istream& bmpFile, BmpInfoHeader& bmpCtx);
};

struct BmpQuad {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
	friend std::istream& operator>>(std::istream& bmpFile, BmpQuad& bmpCtx);
};

struct BmpLine {
	unsigned char imgData; // 128 = 8 * 16
};

std::istream& operator>>(std::istream& bmpFile, BmpFileHeader& bmpFileHeader)
{
	for (auto i = 0; i < sizeof(bmpFileHeader.bfType) / sizeof(bmpFileHeader.bfType[0]); ++i) {
		bmpFile >> bmpFileHeader.bfType[i];
	}

	// bmpFile >> int; // error
	bmpFile.read((char*)&bmpFileHeader.bfSize, sizeof(bmpFileHeader.bfSize));
	bmpFile.read((char*)&bmpFileHeader.bfReserved1, sizeof(bmpFileHeader.bfReserved1));
	bmpFile.read((char*)&bmpFileHeader.bfReserved2, sizeof(bmpFileHeader.bfReserved2));
	bmpFile.read((char*)&bmpFileHeader.bfOffBits, sizeof(bmpFileHeader.bfOffBits));

	return bmpFile;
}

std::istream& operator>>(std::istream& bmpFile, BmpInfoHeader& bmpInfoHeader)
{
	bmpFile.read((char*)&bmpInfoHeader.biSize, sizeof(bmpInfoHeader.biSize));
	bmpFile.read((char*)&bmpInfoHeader.biWidth, sizeof(bmpInfoHeader.biWidth));
	bmpFile.read((char*)&bmpInfoHeader.biHeight, sizeof(bmpInfoHeader.biHeight));
	bmpFile.read((char*)&bmpInfoHeader.biPlanes, sizeof(bmpInfoHeader.biPlanes));
	bmpFile.read((char*)&bmpInfoHeader.biBitCount, sizeof(bmpInfoHeader.biBitCount));
	bmpFile.read((char*)&bmpInfoHeader.biCompression, sizeof(bmpInfoHeader.biCompression));
	bmpFile.read((char*)&bmpInfoHeader.biSizeImage, sizeof(bmpInfoHeader.biSizeImage));
	bmpFile.read((char*)&bmpInfoHeader.biXpelsPerMeter, sizeof(bmpInfoHeader.biXpelsPerMeter));
	bmpFile.read((char*)&bmpInfoHeader.biYpelsPerMeter, sizeof(bmpInfoHeader.biYpelsPerMeter));
	bmpFile.read((char*)&bmpInfoHeader.biClrUsed, sizeof(bmpInfoHeader.biClrUsed));
	bmpFile.read((char*)&bmpInfoHeader.biClrImportant, sizeof(bmpInfoHeader.biClrImportant));
	return bmpFile;
}

std::istream& operator>>(std::istream& bmpFile, BmpQuad& bmpQuad)
{
	bmpFile >> bmpQuad.rgbBlue;
	bmpFile >> bmpQuad.rgbGreen;
	bmpFile >> bmpQuad.rgbRed;
	bmpFile >> bmpQuad.rgbReserved;
	return bmpFile;
}

std::ostream& operator<<(std::ostream& bmpFile, const BmpFileHeader& bmpFileHeader)
{
	for (auto i = 0; i < sizeof(bmpFileHeader.bfType) / sizeof(bmpFileHeader.bfType[0]); ++i) {
		bmpFile << bmpFileHeader.bfType[i];
	}

	// bmpFile >> int; // error
	bmpFile.write((char*)&bmpFileHeader.bfSize, sizeof(bmpFileHeader.bfSize));
	bmpFile.write((char*)&bmpFileHeader.bfReserved1, sizeof(bmpFileHeader.bfReserved1));
	bmpFile.write((char*)&bmpFileHeader.bfReserved2, sizeof(bmpFileHeader.bfReserved2));
	bmpFile.write((char*)&bmpFileHeader.bfOffBits, sizeof(bmpFileHeader.bfOffBits));

	return bmpFile;
}

std::ostream& operator<<(std::ostream& bmpFile, const BmpInfoHeader& bmpInfoHeader)
{
	bmpFile.write((char*)&bmpInfoHeader.biSize, sizeof(bmpInfoHeader.biSize));
	bmpFile.write((char*)&bmpInfoHeader.biWidth, sizeof(bmpInfoHeader.biWidth));
	bmpFile.write((char*)&bmpInfoHeader.biHeight, sizeof(bmpInfoHeader.biHeight));
	bmpFile.write((char*)&bmpInfoHeader.biPlanes, sizeof(bmpInfoHeader.biPlanes));
	bmpFile.write((char*)&bmpInfoHeader.biBitCount, sizeof(bmpInfoHeader.biBitCount));
	bmpFile.write((char*)&bmpInfoHeader.biCompression, sizeof(bmpInfoHeader.biCompression));
	bmpFile.write((char*)&bmpInfoHeader.biSizeImage, sizeof(bmpInfoHeader.biSizeImage));
	bmpFile.write((char*)&bmpInfoHeader.biXpelsPerMeter, sizeof(bmpInfoHeader.biXpelsPerMeter));
	bmpFile.write((char*)&bmpInfoHeader.biYpelsPerMeter, sizeof(bmpInfoHeader.biYpelsPerMeter));
	bmpFile.write((char*)&bmpInfoHeader.biClrUsed, sizeof(bmpInfoHeader.biClrUsed));
	bmpFile.write((char*)&bmpInfoHeader.biClrImportant, sizeof(bmpInfoHeader.biClrImportant));
	return bmpFile;
}

std::ostream& operator<<(std::ostream& bmpFile, const BmpQuad& bmpQuad)
{
	bmpFile << bmpQuad.rgbBlue;
	bmpFile << bmpQuad.rgbRed;
	bmpFile << bmpQuad.rgbReserved;
	return bmpFile;
}

BmpFile::BmpFile(const std::string& bmpFile) :m_bmpFile(bmpFile) {}

BmpFile::~BmpFile() {}

std::istream& BmpFile::Read(BmpCtx &bmpCtx)
{

	std::istream& bmpFile = *this;

	this->open(m_bmpFile, std::ios::binary | std::ios::in); // binary is important
	if (!this->is_open()) {
		std::cout << "open error" << std::endl;
	}
	bmpFile >> bmpFileHeader;
	bmpFile >> bmpInfoHeader;

	bmpQuad.resize(2);
	for (auto& iter : bmpQuad) {
		bmpFile >> iter;
	}

	bmpCtx.Resize(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
	bmpCtx.SetBitWidth(8);
	bmpFile >> bmpCtx;

	return *this;
}
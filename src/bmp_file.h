#ifndef __BMP_FILE__
#define __BMP_FILE__

#include <iostream>
#include <fstream>
#include "bmp_pix.h"
#include "bmp_ctx.h"

class BmpCtx;

struct BmpFileHeader {
	char bfType[2];
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
	friend std::istream& operator>>(std::istream& bmpFile, BmpFileHeader& bmpCtx);
	friend std::ostream& operator<<(std::ostream& bmpFile, const BmpFileHeader& bmpCtx);
};

struct BmpInfoHeader {
	unsigned int biSize;
	long biWidth;
	long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount; // 2^1 biBitCountÖÖÑÕÉ«
	unsigned int biCompression;
	unsigned int biSizeImage;
	long biXpelsPerMeter;
	long biYpelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
	friend std::istream& operator>>(std::istream& bmpFile, BmpInfoHeader& bmpCtx);
	friend std::ostream& operator<<(std::ostream& bmpFile, const BmpInfoHeader& bmpCtx);
};

struct BmpQuad {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
	friend std::istream& operator>>(std::istream& bmpFile, BmpQuad& bmpCtx);
	friend std::ostream& operator<<(std::ostream& bmpFile, const BmpQuad& bmpCtx);
};

struct BmpLine {
	unsigned char imgData; // 128 = 8 * 16
};

class BmpFile : public std::fstream {
public:
	BmpFile(const std::string& bmpFile);
	~BmpFile();
	std::istream& Read(BmpCtx& bmpCtx);
private:
	std::string m_bmpFile;
	BmpFileHeader bmpFileHeader;
	BmpInfoHeader bmpInfoHeader;
	std::vector<BmpQuad> bmpQuad;
};

#endif
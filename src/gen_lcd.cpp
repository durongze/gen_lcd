// gen_lcd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "bmp_file.h"

void Usage(int argc, char** argv, std::ostream &os)
{
    os << argv[0] << " <bmpFile>" << std::endl ;
}

int ProcBmpFile(const char* bmpFileName) 
{
    BmpFile bmpFile(bmpFileName);
    BmpCtx bmpCtx(0, 0, 0);
    LcdCtx lcdCtx(0, 0, 0);
    bmpFile.Read(bmpCtx);
    bmpCtx.Dump(std::cout);
    bmpCtx.ToLcdCtx(lcdCtx);
    lcdCtx.Dump(std::cout);
    return 0;
}

int main(int argc, char** argv)
{
    std::string bmpFileName = "./wheat.bmp";
    return ProcBmpFile(bmpFileName.c_str());
    if (argc == 2) {
        Usage(argc, argv, std::cout);
        return 1;
    }
    else {
        return ProcBmpFile(argv[1]);
    }
}



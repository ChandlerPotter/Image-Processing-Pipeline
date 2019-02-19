#include <PNMreaderCPP.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

PNMreaderCPP::PNMreaderCPP(char *file)
{
	filename = new char[strlen(file) + 1];
	strcpy(filename, file);
};

void PNMreaderCPP::Execute()
{

	ifstream f_in;
	f_in.open(filename);

	char magicNum[128];
	int  width, height, maxval;
	f_in >> magicNum >> width >> height >> maxval;

	Pixel *pixel = new Pixel[width * height];
	GetOutput()->ResetSize(width, height);

	f_in.ignore(256,'\n');
	GetOutput()->setPixel(pixel);
	f_in.read((char *) pixel, sizeof(pixel)*width*height);
	GetOutput()->setPixel(pixel);

	f_in.close();

}


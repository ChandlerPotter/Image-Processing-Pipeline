#include <PNMwriterCPP.h>	
#include <iostream>
#include <fstream>
using namespace std;


void PNMwriterCPP::Write(char *filename)
{
	ofstream f_out;
	f_out.open(filename);
	int w = getImage()->getWidth();
	int h = getImage()->getHeight();

	f_out << "P6\n" << w << " " << h << '\n' << 255 << endl;

	f_out.write((char *) getImage()->getPixel(), sizeof(Pixel)*w*h);
	f_out.close();
}
#include <PNMwriter.h>
#include <stdio.h>

void PNMwriter::Write(char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "w");

	fprintf(f_out, "%s\n%d %d\n%d\n","P6", getImage()->getWidth(), getImage()->getHeight(), 255); 
	fwrite(getImage()->getPixel(), sizeof(Pixel), getImage()->getWidth() * getImage()->getHeight(), f_out); 

	fclose(f_out);
}
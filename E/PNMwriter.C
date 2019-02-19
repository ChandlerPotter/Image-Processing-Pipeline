#include <PNMwriter.h>
#include <stdio.h>

void PNMwriter::Write(char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "w");

	fprintf(f_out, "%s\n%d %d\n%d\n","P6", img1->getWidth(), img1->getHeight(), 255); 
	fwrite(img1->getPixel(), sizeof(Pixel), img1->getWidth() * img1->getHeight(), f_out); 
	fclose(f_out);
}
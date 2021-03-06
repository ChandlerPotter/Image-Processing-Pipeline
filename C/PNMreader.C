#include <PNMreader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PNMreader::PNMreader(char *file)
{
	filename = new char[strlen(file) + 1];
	strcpy(filename, file);
};

void PNMreader::Execute()
{
 FILE *f_in;
 f_in = fopen(filename, "r");

 char magicNum[128];
 int width, height, maxval;
 fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);  

 Pixel *pixel = (Pixel *) malloc(width * height * sizeof(Pixel)); 
 GetOutput()->setPixel(pixel);
 GetOutput()->ResetSize(width, height);

 fread(pixel, sizeof(Pixel), width * height, f_in);
 fclose(f_in);
}
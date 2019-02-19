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

//if filename is not valid filename return error/exception
 FILE *f_in;
 f_in = fopen(filename, "r");

 if (f_in == NULL)
 {
 	char msg[128];
	sprintf(msg, "%s: filename not valid", SourceName());
	DataFlowException e(SourceName(),	msg);
	throw e;
 }

 char magicNum[128];
 int width, height, maxval;
 fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);  

 Pixel *pixel = new Pixel[width*height]; 
 img.setPixel(pixel);
 img.ResetSize(width, height);


 fread(pixel, sizeof(Pixel), width * height, f_in);
 fclose(f_in);
}

void PNMreader::Update()
{
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing",	SourceName());
	Logger::LogEvent(msg);
}

const char *PNMreader::SourceName()
{
	return "PNMreader";
}
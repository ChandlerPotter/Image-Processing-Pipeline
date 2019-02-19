#include <filter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cerr;
using std::endl;


void Filter::Update()
{

//need to change this, make a subclasses Doubleinputfitler and Singleinputfilter...
	char msg[128];
	if (img1 != NULL){
		sprintf(msg, "%s: about to update input1", SourceName());
		Logger::LogEvent(msg);
		img1->Update();
		sprintf(msg, "%s: done updating input1", SourceName());
		Logger::LogEvent(msg);
	}
	if (img2 != NULL){
		sprintf(msg, "%s: about to update input2", SourceName());
		Logger::LogEvent(msg);
		img2->Update();
		sprintf(msg, "%s: done updating input2", SourceName());
		Logger::LogEvent(msg);
	}
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
}

const char * Filter::SourceName(){
	return FilterName();
}
const char * Filter::SinkName(){
	return FilterName();
}

void Shrinker::Execute()
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	int fullW = (img1->getWidth());
	int fullH = (img1->getHeight());
	int halfW = fullW/2;
	int halfH = fullH/2;

	img.ResetSize(halfW, halfH);
	img.setMaxV(255);

	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * halfW * halfH);

	Pixel *pix = img1->getPixel();

	for(int i = 0; i < halfH; i++) {
		for(int j = 0; j < halfW; j++) {
			int in = (i*2*(fullW)+j*2);
			int out = (i*halfW+j);
			pixel[out].red = pix[in].red;
			pixel[out].green = pix[in].green;
			pixel[out].blue = pix[in].blue; 	
		}	
	}
	img.setPixel(pixel);
}

void LRCombine::Execute()
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int Lwidth = img1->getWidth();
	int Lheight = img1->getHeight();
	int Rwidth = img2->getWidth();
	int Rheight = img2->getHeight();


	int combinedWidth = Lwidth + Rwidth;
	int _height = Lheight;

	if	(Lheight != Rheight)
		{
			char msg[128];
			sprintf(msg, "%s: heights must match: %d, %d", SinkName(), Lheight, Rheight);
			DataFlowException e(SinkName(), msg);
			throw e;
		}
	
	img.ResetSize(combinedWidth, _height);

	img.setMaxV(255);
	
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * combinedWidth * _height);
	//Pixel *pixel = new Pixel[combinedWidth * _height];

	Pixel *left_pix = img1->getPixel();

	for(int i = 0; i < Lwidth; i++) {	
		for(int j = 0; j < _height; j++) {
			int out = (j*combinedWidth+i); 	
			int in = (j*Lwidth+i);
			pixel[out].red = left_pix[in].red;				
			pixel[out].green = left_pix[in].green;				
			pixel[out].blue = left_pix[in].blue;				
		}
	}
	
	Pixel *right_pix = img2->getPixel();

	for(int i = 0; i < Rwidth; i++) {
		for(int j = 0; j < _height; j++) {
			int out = (j*combinedWidth+Lwidth+i);
			int in = (j*Rwidth+i);
			pixel[out].red = right_pix[in].red;				
			pixel[out].green = right_pix[in].green;				
			pixel[out].blue = right_pix[in].blue;		
		}
	}
	img.setPixel(pixel);
}


void TBCombine::Execute()
{

	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int Twidth = img1->getWidth();
	int Theight = img1->getHeight();
	int Bwidth = img2->getWidth();
	int Bheight = img2->getHeight();


	int combinedHeight = Theight + Bheight;
	int _width = (Twidth + Bwidth)/2;


	if	(Twidth != Bwidth)
		{
			char msg[128];
			sprintf(msg, "%s: widths must match: %d, %d", SinkName(), Twidth, Bwidth);
			DataFlowException e(SinkName(),	msg);
			throw e;
		}
	img.ResetSize(_width, combinedHeight);
	
	img.setMaxV(255);
	
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * combinedHeight);

	Pixel *top_pix = img1->getPixel();

	for(int i = 0; i < _width; i++) {	
		for(int j = 0; j < Theight; j++) {
			int out = (j*_width+i); 	
			int in = (j*Twidth+i);
			pixel[out].red = top_pix[in].red;				
			pixel[out].green = top_pix[in].green;				
			pixel[out].blue = top_pix[in].blue;				
		}
	}

	Pixel *bottom_pix = img2->getPixel();
	
	for(int i = 0; i < _width; i++) {
		for(int j = 0; j < Bheight; j++) {
			int out = ((j+Theight)*_width+i);
			int in = (j*Bwidth+i);
			pixel[out].red = bottom_pix[in].red;				
			pixel[out].green = bottom_pix[in].green;				
			pixel[out].blue = bottom_pix[in].blue;		
		}
	}
	img.setPixel(pixel);
	
}

void Blender::Execute()
{

	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width1 = img1->getWidth();
	int height1 = img1->getHeight();
	int width2 = img2->getWidth();
	int height2 = img2->getHeight();
	

	int _height = (height1 + height2)/2;
	int _width = (width1 + width2)/2;

	if	(width1 != width2 || height1 != height2)
		{
			char msg[128];
			sprintf(msg, "%s: imgae sizes must match: %d x %d, %d x %d", SinkName(), width1, height1, width2, height2);
			DataFlowException e(SinkName(),	msg);
			throw e;
		}
	img.ResetSize(_width,_height);

	img.setMaxV(255);
	
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * _height);

	Pixel *img1_pix = img1->getPixel();
	Pixel *img2_pix = img2->getPixel();

	for(int i=0; i < _width; i++) {	
		for(int j=0; j < _height; j++) {
			int val = (j*_width+i); 
			pixel[val].red = img1_pix[val].red * factor + img2_pix[val].red * (1-factor);				
			pixel[val].green = img1_pix[val].green * factor + img2_pix[val].green * (1-factor);	
			pixel[val].blue = img1_pix[val].blue * factor + img2_pix[val].blue * (1-factor);					
		}
	}
	img.setPixel(pixel);
}

void Mirror::Execute()
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _width = img1->getWidth();
	int _height = img1->getHeight();

	img.ResetSize(_width,_height);
	img.setMaxV(255);

	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * _height);
	Pixel *pix = img1->getPixel();

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; i++) {
			int in = (i*_width+j);
			int out = (i*_width) + (i*_width - j);
			pixel[out].red = pixel[in].red
			pixel[out].green = pixel[in].green
			pixel[out].blue = pixel[in].blue
		}
	}

	img.setPixel(pixel);
}

void Rotate::Execute()
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _width = img1->getWidth();
	int _height = img1->getHeight();

	img.setMaxV(255);

	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * _height);
	Pixel *pix = img1->getPixel();

}

void Subtract::Execute()
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width1 = img1->getWidth();
	int height1 = img1->getHeight();
	int width2 = img2->getWidth();
	int height2 = img2->getHeight();

	img.setMaxV(255);

	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * _height);
	Pixel *pix = img1->getPixel();
}

void CheckSum::OutputCheckSum(const char *filename)
{
	if(img1 == NULL) {
		char msg[128];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;

	int _height = img1->getHeight();
	int _width = img1->getWidth();
	Pixel *pix = img1->getPixel();

	for (int i = 0; i < _height*_width; i++)
	{
		red += pix[i].red;
		green += pix[i].green;
		blue += pix[i].blue;
	}

	fprintf(filename, "CHECKSUM: %s, %s, %s\n", red, green, blue);
	fclose(filename);
}
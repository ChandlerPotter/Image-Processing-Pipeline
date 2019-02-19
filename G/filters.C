#include <filter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
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
	char msg[128];
	if(img1 == NULL) {
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

	Pixel *pixel = new Pixel[halfW * halfH];
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
	//delete[] pixel;
}

void LRCombine::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
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
			sprintf(msg, "%s: heights must match: %d, %d", SinkName(), Lheight, Rheight);
			DataFlowException e(SinkName(), msg);
			throw e;
		}
	
	img.ResetSize(combinedWidth, _height);
	img.setMaxV(255);
	
	
	Pixel *pixel = new Pixel[combinedWidth * _height];
	//Pixel *pixel = (Pixel *) malloc(combinedWidth * _height * sizeof(Pixel));
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
	//delete[] pixel;
}


void TBCombine::Execute()
{

	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
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
	
	Pixel *pixel = new Pixel[_width * combinedHeight];
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
	//delete[] pixel;
}

void Blender::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
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
	
	Pixel *pixel = new Pixel[_width * _height];
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
	//delete[] pixel;
}

void Mirror::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _width = img1->getWidth();
	int _height = img1->getHeight();

	img.ResetSize(_width,_height);
	img.setMaxV(255);

	Pixel *pixel = new Pixel[_width * _height];
	Pixel *pix = img1->getPixel();

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			int out = (i*_width+j);
			int in = (i*_width) + (_width - 1 - j);
			pixel[out].red = pix[in].red;
			pixel[out].green = pix[in].green;
			pixel[out].blue = pix[in].blue;
		}
	}

	img.setPixel(pixel);
	//delete[] pixel;
}

void Rotate::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _width = img1->getWidth();
	int _height = img1->getHeight();
	int outHeight = _width;
	int outWidth = _height;

	img.ResetSize(outWidth, outHeight);
	img.setMaxV(255);

	Pixel *pixel = new Pixel[outWidth * outHeight];
	Pixel *pix = img1->getPixel();

	for (int i = 0; i < outHeight; i++){
		for (int j = 0; j < outWidth; j++){
			int out = i*outWidth + j;
			int in = (_height- 1 - j) * _width + i;
			pixel[out].red = pix[in].red;
			pixel[out].green = pix[in].green;
			pixel[out].blue = pix[in].blue;
		}
	}
	img.setPixel(pixel);
	//delete[] pixel;
}

void Subtract::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width1 = img1->getWidth();
	int height1 = img1->getHeight();
	int width2 = img2->getWidth();
	int height2 = img2->getHeight();

	if((height1 != height2)){
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), height1, height2);
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if((width1 != width2)){
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), width1, width2);
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	img.ResetSize(width1, height1);
	img.setMaxV(255);

	Pixel *pixel = new Pixel[width1 * height1];
	Pixel *pix1 = img1->getPixel();
	Pixel *pix2 = img2->getPixel();

	for (int i = 0; i < height1*width1; i++){
		if (pix1[i].red > pix2[i].red){
			pixel[i].red = pix1[i].red - pix2[i].red;
		}else{
			pixel[i].red = 0;
		}
		if (pix1[i].green > pix2[i].green){
			pixel[i].green = pix1[i].green - pix2[i].green;
		}else{
			pixel[i].green = 0;
		}
		if (pix1[i].blue > pix2[i].blue){
			pixel[i].blue = pix1[i].blue - pix2[i].blue;
		}else{
			pixel[i].blue = 0;
		}

		}
	img.setPixel(pixel);
	//delete[] pixel;
	}


void CheckSum::OutputCheckSum(const char *filename)
{

	FILE *f;
	f = fopen(filename, "w");
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	int red = 0;
	int green = 0;
	int blue = 0;

	int _height = img1->getHeight();
	int _width = img1->getWidth();
	Pixel *pix = img1->getPixel();

	for (int i = 0; i < _height; i++){
		for (int j = 0; j < _width; j++){
		int n = i*_width+j;
		red += pix[n].red;
		green += pix[n].green;
		blue += pix[n].blue;

		red %= 256;
		green %= 256;
		blue %= 256;
		}
	}

	fprintf(f,"CHECKSUM: %d, %d, %d\n", red, green, blue);
	fclose(f);


}

Color::Color(int w, int h, unsigned char r, unsigned char  g, unsigned char b)
{
	width = w;
	height = h;
	red = r;
	green = g;
	blue = b;
}

void Color::Execute()
{
	img.ResetSize(width, height);
	char msg[128];
	if (red > 255 || red < 0) {    
        sprintf(msg, "%s: red value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (green > 255 || green < 0) {
        sprintf(msg, "%s: green value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (blue > 255 || blue < 0) {
        sprintf(msg, "%s: blue value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    Pixel *pixel = new Pixel[width*height];

    for (int i = 0; i < width*height; i++){
    	pixel[i].red = red;
    	pixel[i].green = green;
    	pixel[i].blue = blue;
    }
    img.setPixel(pixel);
    //delete[] pixel;
}

void Grayscale::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _height = img1->getHeight();
	int _width = img1->getWidth();

	img.ResetSize(_width, _height);
	img.setMaxV(255);

	Pixel *pix = img1->getPixel();
	Pixel *pixel = new Pixel[_width*_height];

	for (int i = 0; i < _height*_width; i++){
		int car = (pix[i].red/5) + (pix[i].green/2) + (pix[i].blue/4);
		pixel[i].red = (unsigned char) car;
		pixel[i].green = (unsigned char) car;
		pixel[i].blue = (unsigned char) car;
	}

	img.setPixel(pixel);
	//delete[] pixel;
}

void Blur::Execute()
{
	char msg[128];
	if(img1 == NULL) {
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int _height = img1->getHeight();
	int _width = img1->getWidth();

	img.ResetSize(_width, _height);
	img.setMaxV(255);
	int h = img.getHeight();
	int w = img.getWidth();

	Pixel *pix = img1->getPixel();
	Pixel *pixel = new Pixel[w*h];

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (i == (h-1) || j == (w-1) || (i == 0) || (j == 0)){
				int in = i*w+j;
				pixel[in].red = pix[in].red;
				pixel[in].green = pix[in].green;
				pixel[in].blue = pix[in].blue;
			}else{
				int in = i*w+j;
				int other1 = (i-1)*w;
				int other2 = i*w;
				int other3 = (i+1)*w;
				pixel[in].red =  pix[other1+j-1].red/8 + 
								pix[other1+j].red/8 + 
								pix[other1+j+1].red/8 + 
						   		pix[other2+j-1].red/8 + 
								pix[other2+j+1].red/8 +
						   		pix[other3+j-1].red/8 + 
								pix[other3+j].red/8 + 
								pix[other3+j+1].red/8;
				pixel[in].green =  pix[other1+j-1].green/8 + 
								pix[other1+j].green/8 + 
								pix[other1+j+1].green/8 + 
						   		pix[other2+j-1].green/8 + 
								pix[other2+j+1].green/8 +
						   		pix[other3+j-1].green/8 + 
								pix[other3+j].green/8 + 
								pix[other3+j+1].green/8;
				pixel[in].blue =  pix[other1+j-1].blue/8 + 
								pix[other1+j].blue/8 + 
								pix[other1+j+1].blue/8 + 
						   		pix[other2+j-1].blue/8 + 
								pix[other2+j+1].blue/8 +
						   		pix[other3+j-1].blue/8 + 
								pix[other3+j].blue/8 + 
								pix[other3+j+1].blue/8;


			}
		}
	}

	img.setPixel(pixel);
	//delete[] pixel;
}
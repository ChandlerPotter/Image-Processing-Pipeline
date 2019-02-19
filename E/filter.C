#include <filter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Filter::Update()
{

	if (img1 != NULL){
		img1->Update();
	}
	if (img2 != NULL){
		img2->Update();
	}

	Execute();
}

void Shrinker::Execute()
{
	int fullW = (img1->getWidth());
	int fullH = (img1->getHeight());
	int halfW = fullW/2;
	int halfH = fullH/2;

	img.ResetSize(halfW, halfH);
	img.setMaxV(255);

	//Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * halfW * halfH);
	Pixel *pixel = new Pixel[halfW*halfH];
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
	//free(pixel);
	delete [] pixel;
}
void LRCombine::Execute()
{
	int Lwidth = img1->getWidth();
	int Lheight = img1->getHeight();
	int Rwidth = img2->getWidth();
	int Rheight = img2->getHeight();


	int combinedWidth = Lwidth + Rwidth;
	int _height = (Lheight + Rheight)/2;
	img.ResetSize(combinedWidth, _height);

	img.setMaxV(255);
	
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * combinedWidth * _height);

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
	//free(pixel);
	
}

void TBCombine::Execute()
{
	int Twidth = img1->getWidth();
	int Theight = img1->getHeight();
	int Bwidth = img2->getWidth();
	int Bheight = img2->getHeight();


	int combinedHeight = Theight + Bheight;
	int _width = (Twidth + Bwidth)/2;
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
	//free(pixel);
	
}

void Blender::Execute()
{
	int width1 = img1->getWidth();
	int height1 = img1->getHeight();
	int width2 = img2->getWidth();
	int height2 = img2->getHeight();
	

	int _height = (height1 + height2)/2;
	int _width = (width1 + width2)/2;
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
	//free(pixel);
}
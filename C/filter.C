#include <filter.h>
#include <stdio.h>

void Shrinker::Execute()
{
	Image *output = getImage(); 
	Image *img = GetOutput();  
	
	int fullW = (output->getWidth());
	int fullH = (output->getHeight());
	int halfW = fullW/2;
	int halfH = fullH/2;

	img->ResetSize(halfW, halfH);
	img->setMaxV(255);

	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * halfW * halfH);

	Pixel *pix = output->getPixel();

	for(int i = 0; i < halfH; i++) {
		for(int j = 0; j < halfW; j++) {
			int in = (i*2*(fullW)+j*2);
			int out = (i*halfW+j);
			pixel[out].red = pix[in].red;
			pixel[out].green = pix[in].green;
			pixel[out].blue = pix[in].blue; 	
		}	
	}
	img->setPixel(pixel);
}

void LRCombine::Execute()
{
	int Lwidth = getImage()->getWidth();
	int Lheight = getImage()->getHeight();
	int Rwidth = getImage2()->getWidth();
	int Rheight = getImage2()->getHeight();

	Image *img = GetOutput();
	Image *left = getImage();
	Image *right = getImage2();

	int combinedWidth = Lwidth + Rwidth;
	int _height = (Lheight + Rheight)/2;
	img->ResetSize(combinedWidth, _height);

	GetOutput()->setMaxV(255);
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * combinedWidth * _height);

	Pixel *left_pix = left->getPixel();

	for(int i = 0; i < Lwidth; i++) {	
		for(int j = 0; j < _height; j++) {
			int out = (j*combinedWidth+i); 	
			int in = (j*Lwidth+i);
			pixel[out].red = left_pix[in].red;				
			pixel[out].green = left_pix[in].green;				
			pixel[out].blue = left_pix[in].blue;				
		}
	}
	
	Pixel *right_pix = right->getPixel();

	for(int i = 0; i < Rwidth; i++) {
		for(int j = 0; j < _height; j++) {
			int out = (j*combinedWidth+Lwidth+i);
			int in = (j*Rwidth+i);
			pixel[out].red = right_pix[in].red;				
			pixel[out].green = right_pix[in].green;				
			pixel[out].blue = right_pix[in].blue;		
		}
	}
	img->setPixel(pixel);
}

void TBCombine::Execute()
{
	int Twidth = getImage()->getWidth();
	int Theight = getImage()->getHeight();
	int Bwidth = getImage2()->getWidth();
	int Bheight = getImage2()->getHeight();

	Image *img = GetOutput();
	Image *top = getImage();
	Image *bottom = getImage2();

	int combinedHeight = Theight + Bheight;
	int _width = (Twidth + Bwidth)/2;
	img->ResetSize(_width, combinedHeight);
	
	img->setMaxV(255);
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * combinedHeight);

	Pixel *top_pix = top->getPixel();

	for(int i = 0; i < _width; i++) {	
		for(int j = 0; j < Theight; j++) {
			int out = (j*_width+i); 	
			int in = (j*Twidth+i);
			pixel[out].red = top_pix[in].red;				
			pixel[out].green = top_pix[in].green;				
			pixel[out].blue = top_pix[in].blue;				
		}
	}

	Pixel *bottom_pix = bottom->getPixel();
	
	for(int i = 0; i < _width; i++) {
		for(int j = 0; j < Bheight; j++) {
			int out = ((j+Theight)*_width+i);
			int in = (j*Bwidth+i);
			pixel[out].red = bottom_pix[in].red;				
			pixel[out].green = bottom_pix[in].green;				
			pixel[out].blue = bottom_pix[in].blue;		
		}
	}
	img->setPixel(pixel);
}

void Blender::Execute()
{
	int width1 = getImage()->getWidth();
	int height1 = getImage()->getHeight();
	int width2 = getImage2()->getWidth();
	int height2 = getImage2()->getHeight();

	Image *img = GetOutput();
	Image *img1 = getImage();
	Image *img2 = getImage2();

	int _height = (height1 + height2)/2;
	int _width = (width1 + width2)/2;
	img->ResetSize(_width,_height);

	img->setMaxV(255);
	Pixel *pixel = (Pixel *) malloc(sizeof(Pixel) * _width * _height);

	Pixel *img1_pix = img1->getPixel();
	Pixel *img2_pix = img2->getPixel();

	for(int i=0; i < _width; i++) {	
		for(int j=0; j < _height; j++) {
			int val = (j*_width+i); 
			pixel[val].red = img1_pix[val].red * factor + img2_pix[val].red * (1-factor);				
			pixel[val].green = img1_pix[val].green * factor + img2_pix[val].green * (1-factor);	
			pixel[val].blue = img1_pix[val].blue * factor + img2_pix[val].blue * (1-factor);					}
	}
	img->setPixel(pixel);
}
#include <stdlib.h>
#include <string.h>
#ifndef IMAGE_H
#define IMAGE_H

struct Pixel 
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class Image
{
	private:
		int width;
		int height; 
		int maxval;
		Pixel *p;

	public:
		Image(void);
		Image(int width, int height);
		Image(Image &img);

		void ResetSize(int _width, int _height);
		int getWidth() {return width;}
		int getHeight() {return height;}
		int getMaxV() {return maxval;}
		void setMaxV(int _maxval) {maxval = _maxval;};
		Pixel * getPixel() {return p;}
		void setPixel(Pixel *pixel){p = pixel;};

};
#endif 
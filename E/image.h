#include <stdlib.h>
#include <string.h>
#ifndef IMAGE_H
#define IMAGE_H

class Source;

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
		Source *s;

	public:
		Image(void); //default
		Image(int width, int height); //paramaretized
		Image(Image &img);

		void ResetSize(int _width, int _height);
		int getWidth() {return width;}
		int getHeight() {return height;}
		int getMaxV() {return maxval;}
		void setMaxV(int _maxval) {maxval = _maxval;};
		Pixel * getPixel() {return p;}
		void setPixel(Pixel *pixel);
		void Update();
		void setSource(Source *source);
		Source * getSource() {return s;};

};
#endif 
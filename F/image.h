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
		Image(void);
		Image(int width, int height);
		Image(Image &img);

		void ResetSize(int _width, int _height);

		int getWidth() {return width;}
		int getHeight() {return height;}
		int getMaxV() {return maxval;}
		Pixel * getPixel() {return p;}
		Source * getSource() {return s;};

		void setMaxV(int _maxval) {maxval = _maxval;};
		void setPixel(Pixel *pixel){p = pixel;};
		void setSource(Source *source);

		void Update();
		

};
#endif 
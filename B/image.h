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

struct Image
{
	//could make private, but then would need public getter methods? ask in OH.
	public:
		int width;
		int height; 
		int maxval;
		Pixel *p;

	public:
		Image(void);
		Image(int width, int height);
		Image(Image &img);

		void ResetSize(int _width, int _height);

};
#endif 
#include <image.h>

Image::Image(void)
{
	width = 0;
	height = 0;
	maxval = 0;
	p = NULL;
}

Image::Image(int _width, int _height)
{
	width = _width;
	height = _height;
	maxval = 255;
	p = (Pixel *) malloc(sizeof(Pixel) * width * height);
}

Image::Image(Image &img)
{
	width = img.width;
	height = img.height;
	maxval = img.maxval;
	p = (Pixel *) malloc(sizeof(Pixel) * width * height);
	memcpy(p, img.p, sizeof(Pixel)* width * height);
}

void Image::ResetSize(int _width, int _height)
{
	width = _width;
	height = _height;
}
#include <string.h>
#include <image.h>
#ifndef SINK_H
#define SINK_H

class Sink
{
	protected:
		Image *img1, *img2;

	public:
		Sink();
		//~Sink();
		void SetInput(Image *image1);
		void SetInput2(Image *image2);
		Image * getImage() {return img1;}
		Image * getImage2() {return img2;}
		virtual const char *SinkName() = 0;
};

#endif
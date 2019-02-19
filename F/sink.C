#include <sink.h>

Sink::Sink()
{
	img1 = NULL;
	img2 = NULL;
}
void Sink::SetInput(Image *image1)
{
	img1 = image1;
}

void Sink::SetInput2(Image *image2)
{
	img2 = image2;
}

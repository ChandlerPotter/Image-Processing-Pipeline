#include <source.h>
#include <stdio.h>

Source::Source(void)
{
	img.setSource(this);
//	printf("img = %p\n" , img.getSource());
}

Image *Source::GetOutput(void)
{
	return &img;
}

void Source::Update()
{
	Execute();
}

#include <stdlib.h>
#include <string.h>
#include <image.h>
#ifndef SOURCE_H
#define SOURCE_H

class Source
{
	private:
		Image img;

	public:
		virtual void Execute(void) = 0;
		Image * GetOutput();
};

#endif
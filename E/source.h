#include <stdlib.h>
#include <string.h>
#include <image.h>
#ifndef SOURCE_H
#define SOURCE_H

class Source
{
	protected:
		Image img;
		virtual void Execute(void) = 0;

	public:
		Source();
		Image * GetOutput();
		virtual void Update();
};

#endif
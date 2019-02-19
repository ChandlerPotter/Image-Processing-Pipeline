#include <sink.h>
#include <image.h>
#include <iostream>
#ifndef PNMWRITER_H
#define PNMWRITER_H


class PNMwriter : public Sink
{
	public:
		void Write(char *filename);
		
};

#endif
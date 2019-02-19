#include <sink.h>
#include <image.h>
#include <iostream>
#ifndef PNMWRITER_H
#define PNMWRITER_H


class PNMwriterCPP : public Sink
{
	public:
		void Write(char *filename);

};

#endif
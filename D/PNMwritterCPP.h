#include <sink.h>
#include <image.h>
#include <iostream>
#ifndef PNMWRITERCPP_H
#define PNMWRITERCPP_H


class PNMwriterCPP : public Sink
{
	public:
		void Write(char *filename);

};

#endif
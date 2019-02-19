#include <source.h>
#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreaderCPP : public Source
{
	private:
		char *filename;

	public:
		PNMreaderCPP(char *file);
		~PNMreaderCPP() {free(filename);};

		virtual void Execute();

};

#endif
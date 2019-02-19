#include <source.h>
#include <sink.h>
#include <image.h>
#ifndef FILTERS_H
#define FILTERS_H

class Filter : public Sink, public Source
{
	public:
		virtual void Execute() = 0;
		virtual void Update();
		virtual const char *FilterName() = 0;
		virtual const char *SourceName();
		virtual const char *SinkName();
		//virtual int GetNumberInputs();

};
/*
class DoubleInputFilter: public Filter
{
	public:
		int GetNumberInputs() {return 2;};

};

class SingleInputFilter: public Filter
{
	public:
		int GetNumberInputs() {return 1;};

};
*/
class Shrinker : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName() {return "Shrinker";};

};

class LRCombine : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName() {return "LRCombine";};
};

class TBCombine : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName() {return "TBCombine";};
};

class Blender : public Filter
{
	private:
		double factor;

	public:
		void SetFactor(double f){factor = f;}

		virtual void Execute();
		virtual const char *FilterName() {return "Blender";};
};

#endif

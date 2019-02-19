#include <source.h>
#include <sink.h>
#ifndef FILTER_H
#define FILTER_H

class Filter : public Sink, public Source
{
		virtual void Execute() = 0;
};

class Shrinker : public Filter
{
	public:
		virtual void Execute();

};

class LRCombine : public Filter
{
	public:
		virtual void Execute();
	
};

class TBCombine : public Filter
{
	public:
		virtual void Execute();
};

class Blender : public Filter
{
	private:
		double factor;

	public:
		void SetFactor(double f){factor = f;}

		virtual void Execute();
};

#endif

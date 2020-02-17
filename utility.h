#ifndef UTILITY_H
#define UTILITY_H

#include "image.h"
#include "statistics.h"
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>

enum dimension{ ROW, COL};
enum DPkeys { SUM, EDGE};

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		
		//HW1 parse helper function
		static vector<char*> parse(char* str, int argc);

		//histogram stretching between a and b
		static void linearHistogramStretching(image& tgt, Region roi, int a, int b);
		

};

#endif


#ifndef UTILITY_H
#define UTILITY_H

#include "image.h"
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
		
		//HW1 Thresholding function
		static void thresholding(image &tgt, int t1, int t2, Region roi);

		//HW1 Color Binary function
		static void colorBinarization(image &tgt, Color c, int tc, int dc, Region roi);
		static float colorDistance(Color A, Color B);

		//HW1 smoothing helper
		static Region getSquareWindow(image &img, int ws, int i, int j);
		static Region get1DWindow(image &img, int ws, dimension dim, int i, int j);
		static int averageIntensity(image &img, Region window);

		//HW1 2D smoother
		static void twoDimensionalSmoothing(image &tgt, int ws, Region roi);

		//HW1 1D smoother 
		static void oneDimensionalSmoothing(image &tgt, int ws, Region roi);
		
		//HW1 incremental
		static void incrementalSmoothing(image &tgt, int ws, Region roi);
		static int oneDimSum(image &img, Region window);
};

#endif


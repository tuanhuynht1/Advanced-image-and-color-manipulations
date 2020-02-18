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

		//histogram stretching between a and b, modiefies image and returns image statistics including updated histogram
		static Image_Statistics linearHistogramStretching(image& tgt, Region roi, int a, int b);

		//optimal binarization, binarize image using optimal thresholding and returns image statistics
		static Image_Statistics optimalThresholding(image& tgt, Region roi, double epsilon);

		//takes in a binarize image and and returns the image with the background region overlay
		static Image_Statistics backgound(image& tgt, image& binarized, Region roi);

		//takes in a binarize image and and returns the image with the foreground region overlay
		static Image_Statistics foreground(image& tgt, image& binarized, Region roi);

		// takes an image, separate background and foreground and perform histogram stretching on 
		static Image_Statistics twoLayerHistogramStretching(image& tgt, image& btgt, image& ftgt, Region roi, double epsilon);

		

};

#endif


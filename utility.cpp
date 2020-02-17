#include "utility.h"

#define MAXRGB 255
#define MINRGB 0
#define HISTO_SIZE 256

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

//----------------------Helper Parse Function ----------------//
vector<char*> utility::parse(char* str, int argC){
	vector<char*> arguments;
	char *pch;
	pch = strtok(str, " ");
	arguments.push_back(pch);
	for(int i = 1; i < argC; i++){
		pch = strtok(NULL, " ");
		arguments.push_back(pch);
	}
	return arguments;
}


Image_Statistics utility::linearHistogramStretching(image& tgt, Region roi, int a, int b){
    image* ip = &tgt;
    Image_Statistics stat(ip,roi);
    double stepsize = double(MAXRGB) / (b - a);

	//remap values
	for(int i = 0; i < stat.pixel_map.size(); i++){
		for(int j = 0; j < stat.pixel_map[0].size(); j++){
			int value = stat.pixel_map[i][j];
			if(value < a){
				value = MINRGB;
			}
			else if (value > b){
				value = MAXRGB;
			}
			else{
				double newVal = (value - a) * stepsize;
				value = round(newVal);
			}
			stat.pixel_map[i][j] = value;
		}
	}
	//modify original image according to the new value mapping
	for(int i = roi.i0; i < roi.ilim; i++){
		for(int j = roi.j0; j < roi.jlim; j++){
			tgt.setPixel(i,j,stat.pixel(i,j));
		}
	}
	// tgt.save("newImage.pgm");	
	
	// update statistics and return 
	stat.generateNewHistogram();
	stat.setMode();
	return stat;	
}
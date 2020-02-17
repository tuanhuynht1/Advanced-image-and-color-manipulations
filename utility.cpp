#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

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


void utility::linearHistogramStretching(image& tgt, Region roi, int a, int b){
    image* ip = &tgt;
    Image_Statistics stat(ip,roi);

    float stepsize = float(MAXRGB) / float(b - a);
    // cout << stepsize << endl;

	for(int i = 0; i < stat.pixel_map.size(); i++){
		for(int j = 0; j < stat.pixel_map[0].size(); j++){
			int value = stat.pixel_map[i][j];
			if(value < a){
				stat.pixel_map[i][j] = MINRGB;
			}
			else if (value > b){
				stat.pixel_map[i][j] = MAXRGB;
			}
			else{
				value = int((value - a) * stepsize);
				stat.pixel_map[i][j] = value;
			}
		}
	}
}
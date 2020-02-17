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


void utility::linearHistogramStretching(image& tgt, Region roi, int a, int b){
    image* ip = &tgt;
    Image_Statistics stat(ip,roi);


    float stepsize = float(MAXRGB) / float(b - a);
    cout << stepsize << endl;

	for(int i = 0; i < stat.pixel_map.size(); i++){
		for(int j = 0; j < stat.pixel_map[0].size(); j++){
			int value = stat.pixel_map[i][j];
			// cout << value  << ":";
			if(value < a){
				value = MINRGB;
				// cout << value << " ";
			}
			else if (value > b){
				value = MAXRGB;
				// cout << value << " ";
			}
			else{
				float newVal = (value - a) * stepsize;
				// value = int((value - a) * stepsize);
				// stat.pixel_map[i][j] = value;
				// cout << newVal << ":";
				value = newVal;
				// cout << value << " ";
			}
			stat.pixel_map[i][j] = value;
		}
		// cout << endl;
	}

	stat.generateNewHistogram();
	stat.setMode();

	cout << stat.histogram[stat.mode] << endl;

	image output(HISTO_SIZE,HISTO_SIZE);

    //coefficient for normalizing
    float k = 255.0 / stat.histogram[stat.mode];
	cout << k << endl;
    for(int j = 0; j < HISTO_SIZE; j++){
		cout << j << " ";
        int count = int(stat.histogram[j] * k);  //normalize to fit
        for(int i  = HISTO_SIZE - 1; i > HISTO_SIZE-1 - count; i--){
            output.setPixel(i,j,MAXRGB);    //set each count to appear as a white pixel
        }
    }
    output.save("test2.pgm");


	// return stat;
	// stat.writeHistogramToFile("stretch.pgm");

}
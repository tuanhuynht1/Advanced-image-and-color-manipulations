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

Color_Image_Statistics utility::colorHistogramStretching(image& tgt, Region roi, channel c, int a, int b){
	image* ip = &tgt;
    Color_Image_Statistics stat(ip,roi,c);
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
			tgt.setPixel(i,j,c,stat.pixel(i,j));
		}
	}
	// tgt.save("newImage.ppm");	
	// update statistics and return 
	stat.generateNewHistogram();
	stat.setMode();
	return stat;	
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

Image_Statistics utility::optimalThresholding(image& tgt, Region roi, double epsilon){
	image* ip = &tgt;
    Image_Statistics stat(ip,roi);

	//find the optimal threshold value
	double backgroundMean, objectMean, tprev, t = stat.mean;
	do{
		tprev = t; //previous t value
		stat.setBOmeans(backgroundMean,objectMean,tprev);
		t = (backgroundMean + objectMean) / 2.0;
	}while(abs(tprev - t) > epsilon); 
	
	//apply thresholding to roi
	for(int i = roi.i0; i < roi.ilim; i++){
		for(int j = roi.j0; j < roi.jlim; j++){
			if(tgt.getPixel(i,j) < t){
				tgt.setPixel(i,j,MINRGB);
			}
			else{
				tgt.setPixel(i,j,MAXRGB);
			}
		}
	}
	//return updated image statistics
	return Image_Statistics(ip,roi);

}

Image_Statistics utility::backgound(image& tgt, image& binarized, vector<Region> R){

	for(int r = 0; r < R.size(); r++){
		for(int i = R[r].i0; i < R[r].ilim; i++){
			for(int j = R[r].j0; j < R[r].jlim; j++){
				if(binarized.getPixel(i,j) == MAXRGB){
					tgt.setPixel(i,j,MINRGB);
				}
			}
		}
	}
	
	return Image_Statistics(&tgt,Region(0,0,tgt.getNumberOfRows(),tgt.getNumberOfColumns()));
}

Image_Statistics utility::foreground(image& tgt, image& binarized, vector<Region> R){

	for(int r = 0; r < R.size(); r++){
		for(int i = R[r].i0; i < R[r].ilim; i++){
			for(int j = R[r].j0; j < R[r].jlim; j++){
				if(binarized.getPixel(i,j) == MINRGB){
					tgt.setPixel(i,j,MINRGB);
				}
			}
		}
	}
	
	return Image_Statistics(&tgt,Region(0,0,tgt.getNumberOfRows(),tgt.getNumberOfColumns()));
}

Image_Statistics utility::combine(image& tgt, image& binarized, image& bg, image& fg, vector<Region> R){

	for(int r = 0 ; r < R.size(); r++){
		Region roi = R[r];
		for(int i = roi.i0; i < roi.ilim; i++){
			for(int j = roi.j0; j < roi.jlim; j++){
				//background pixel
				if (binarized.getPixel(i,j) == MINRGB){
					tgt.setPixel(i,j,bg.getPixel(i,j));
				}
				//foreground pixel
				else{
					tgt.setPixel(i,j,fg.getPixel(i,j));
				}
			}
		}
	}
	return Image_Statistics(&tgt,Region(0,0,tgt.getNumberOfRows(),tgt.getNumberOfColumns()));
}

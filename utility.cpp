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

void storage(){
// //----------------------Helper Distance Function ----------------//
// float utility::colorDistance(Color A, Color B){
// 	float R2 = pow(A.r - B.r,2);
// 	float G2 = pow(A.g - B.g,2);
// 	float B2 = pow(A.b - B.b,2);
// 	return sqrt(R2 + G2 + B2);
// }
// //--------------------- Point Functions ----------------------------//
// void utility::thresholding(image &tgt, int t1, int t2, Region roi){
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			int intensity = tgt.getPixel(i,j);
// 			if (intensity >= t1 && intensity < t2){
// 				//set to white
// 				tgt.setPixel(i,j,MAXRGB);
// 			}
// 			else{
// 				//set black
// 				tgt.setPixel(i,j,MINRGB);
// 			} 
// 		}
// 	}
// }

// void utility::colorBinarization(image &tgt, Color c, int tc, int dc, Region roi){
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			//get color at point i,j
// 			Color pixelColor(tgt.getPixel(i,j,RED), tgt.getPixel(i,j,GREEN),tgt.getPixel(i,j,BLUE));
// 			//get distance from c
// 			float distance = colorDistance(c,pixelColor);
// 			//set to black if larger than threshold
// 			if(distance > tc){
// 				tgt.setPixel(i,j,RED,MINRGB);
// 				tgt.setPixel(i,j,GREEN,MINRGB);
// 				tgt.setPixel(i,j,BLUE,MINRGB);
// 			}
// 			//else, increase by dc
// 			else{
// 				tgt.setPixel(i,j,RED,checkValue(tgt.getPixel(i,j,RED) + dc));
// 				tgt.setPixel(i,j,GREEN,checkValue(tgt.getPixel(i,j,GREEN) + dc));
// 				tgt.setPixel(i,j,BLUE,checkValue(tgt.getPixel(i,j,BLUE) + dc));
// 			}
// 		}
// 	}
// }

// //----------------------------------------------------------- Localized Functions ------------------------//
// Region utility::getSquareWindow(image &img, int ws, int i, int j){
// 	int offset = ws / 2;
// 	int imax = img.getNumberOfRows();
// 	int jmax = img.getNumberOfColumns();
// 	if(i + offset >= imax || i - offset < 0 || j + offset >= jmax || j - offset < 0){
// 		return Region(1,1,i,j);
// 	}
// 	else{
// 		return Region(ws, ws, i - offset, j - offset);
// 	}
// }

// Region utility::get1DWindow(image &img, int ws, dimension dim, int i, int j){
// 	int max, offset = ws / 2;
// 	switch (dim){
// 		case ROW:
// 			max = img.getNumberOfColumns();
// 			if (j + offset < max && j - offset >= 0){
// 				return Region(1, ws,i,j - offset);
// 			}
// 		case COL:
// 			max = img.getNumberOfRows();
// 			if (i + offset < max && i - offset >= 0){
// 				return Region(ws, 1,i - offset, j);
// 			}
// 	}
// 	return Region(1,1,i,j);
// }

// int utility::averageIntensity(image &img, Region window){
// 	int pixels = 0, sum = 0;
// 	for (int i = window.i; i < window.i + window.ilen; i++){
// 		for(int j = window.j; j < window.j + window.jlen; j++){
// 			pixels++;
// 			sum += img.getPixel(i,j);
// 		}
// 	}
// 	return sum / pixels;
// }

// void utility::twoDimensionalSmoothing(image &tgt, int ws, Region roi){
// 	image original(tgt);
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			Region window = getSquareWindow(tgt,ws,i,j);
// 			tgt.setPixel(i,j,averageIntensity(original,window));
// 		}
// 	}
// }

// void utility::oneDimensionalSmoothing(image &tgt, int ws, Region roi){
// 	image original(tgt);
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			Region row = get1DWindow(tgt,ws,ROW,i,j);
// 			tgt.setPixel(i,j,averageIntensity(original,row));
// 		}
// 	}
// 	original.copyImage(tgt);
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			Region col = get1DWindow(tgt,ws,COL,i,j);
// 			tgt.setPixel(i,j,averageIntensity(original,col));
// 		}
// 	}
// }

// int utility::oneDimSum(image &img, Region window){
// 	int sum = 0;
// 	//sum along column
// 	if(window.jlen == 1){
// 		for(int i = window.i; i < window.i + window.ilen; i++){
// 			sum += img.getPixel(i,window.j);
// 		}
// 	}
// 	//sum along row
// 	else if (window.ilen == 1) {
// 		for(int j = window.j; j < window.j + window.jlen; j++){
// 			sum += img.getPixel(window.i,j);
// 		}
// 	}
// 	return sum;
// }

// void utility::incrementalSmoothing(image &tgt, int ws, Region roi){
// 	image original(tgt);
// 	int offset = ws / 2;
// 	int sum = 0, prev, next;
// 	int ilim = tgt.getNumberOfRows(), jlim = tgt.getNumberOfColumns();
// 	//horizontal convolution
// 	for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 		for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 			//edge detection
// 			if(j + offset >= jlim){
// 				continue;
// 			}
// 			//initialize pixel of first column of each row
// 			if(j == roi.j){
// 				Region row = get1DWindow(tgt,ws,ROW,i,j);
// 				sum = oneDimSum(original, row);
// 				prev = row.j;
// 				next = row.j + row.jlen;
// 			}
// 			else{
// 				//new sum = prev sum - prev edge + new edge
// 				sum = sum - original.getPixel(i,prev) + original.getPixel(i,next);
// 				prev++;
// 				next++;
// 			}
// 			tgt.setPixel(i,j,sum/ws);
// 		}
// 	}
// 	original.copyImage(tgt);
// 	//vertical convolution
// 	for(int j = roi.j; j < roi.j + roi.jlen; j++){
// 		for(int i = roi.i; i < roi.i + roi.ilen; i++){
// 			//edge detection
// 			if(i + offset >= ilim){
// 				continue;
// 			}
// 			//initialize pixel of first column of each row
// 			if(i == roi.i){
// 				Region col = get1DWindow(tgt,ws,COL,i,j);
// 				sum = oneDimSum(original, col);
// 				prev = col.i;
// 				next = col.i + col.ilen;
// 			}
// 			else{
// 				//new sum = prev sum - prev edge + new edge
// 				sum = sum - original.getPixel(prev,j) + original.getPixel(next,j);
// 				prev++;
// 				next++;
// 			}
// 			tgt.setPixel(i,j,sum/ws);
// 		}
// 	}	
// }

	return;

};


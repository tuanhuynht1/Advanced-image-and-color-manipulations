/************************************************************
*	Advanced image and color manipulation					*
*		Author: Tuan Huynh									*
 ************************************************************/

#include "utility.h"
#include "image.h"
#include "statistics.h"
#include <vector>
#include <chrono>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv){


	Region R(2,2,5,5);
	// cout << R.i0 << " to " << R.ilim << endl;
	// cout << R.j0 << " to " << R.jlim << endl;

	image img, *p;
	img.read(strdup("baboon.pgm"));
	// for(int i = 2; i < 7; i++){
	// 	for(int j = 2; j < 9; j++){
	// 		cout << img.getPixel(i,j) << " ";
	// 	}
	// 	cout << endl;
	// }
	p = &img;

	// cout << endl;
	Image_Statistics stat(p,R);
	cout << endl;
	for(int i = 0; i < 256; i++){
		if(stat.histogram[i] > 0)
		cout << i << ":" << stat.histogram[i] << " ";
	}
	cout << endl << endl;
	cout << stat.mean << endl;

	double bmean, omean;
	stat.setBOmeans(bmean,omean,stat.mean);

	cout << bmean << " " << omean << endl;



	// cout << img.getPixel(90,100) << " " << stat.pixel(90,100) << endl;

	// stat.writeHistogramToFile("test.pgm");
	// cout << stat.pixel_map.size() << " x " << stat.pixel_map[0].size() << endl; 

	// stat = utility::linearHistogramStretching(img,R,100,200);
	// stat.writeHistogramToFile("test2.pgm");























	// image src, tgt;
	// FILE *fp;
	// char str[MAXLEN];
	// char outfile[MAXLEN];

	// if ((fp = fopen(argv[1],"r")) == NULL) {
	// 	fprintf(stderr, "Can't open file: %s\n", argv[1]);
	// 	exit(1);
	// }

	
	// fclose(fp);

	return 0;
}
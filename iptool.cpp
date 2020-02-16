/************************************************************
*	Advanced image and color manipulation					*
*		Author: Tuan Huynh									*
 ************************************************************/

#include "utility.h"
#include "image.h"
#include <vector>
#include <chrono>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv){


	Region R(2,2,5,7);
	cout << R.i0 << " to " << R.ilim << endl;
	cout << R.j0 << " to " << R.jlim << endl;



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
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


	
	image src, *ip;
	FILE *fp;
	char str[MAXLEN];

	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	vector<char*> argV;
	int rows, cols, i_origin, j_origin, number_of_regions;
	string name, op;

	while(fgets(str,MAXLEN,fp) != NULL){

		//parse line into argument Vector for each operation
		argV = utility::parse(str,4);
		src.read(argV[0]);					//input file
		name = argV[1];						//name for basis of output files
		op = argV[2];						//operation		
		number_of_regions = atoi(argV[3]);	//number of roi

		//linear histogram stretching //---------------------------------------------------------------------
		if(op.compare("lhs") == 0){
			
			int a, b;
			for(int i = 0; i < number_of_regions; i++){
				if (fgets(str,MAXLEN,fp) != NULL){

					//read in arguemnts for next roi operation
					argV = utility::parse(str,6);
					i_origin = atoi(argV[0]);
					j_origin = atoi(argV[1]);
					rows = atoi(argV[2]);
					cols = atoi(argV[3]);
					a = atoi(argV[4]);
					b = atoi(argV[5]);

					//initialize roi
					Region roi(i_origin,j_origin,rows,cols);

					//initialize name extension for current region's histogram
					string hist_name = name;
					hist_name += ("_hist" + to_string(i+1));

					//write histogram before stretching
					ip = &src;	//image pointer
					Image_Statistics src_stat(ip,roi);
					src_stat.writeHistogramToFile(hist_name + "_src.pgm");
					
					//perform modification on src
					Image_Statistics stat = utility::linearHistogramStretching(src,roi,a,b);

					//write histogram after stretching
					stat.writeHistogramToFile(hist_name + ".pgm");
				}
			}
			//output final image
			name += "_lhs.pgm";	//operation signature
			src.save(name.c_str());
		}

		//optimal thresholding //-----------------------------------------------------------------------------
		if(op.compare("opt") == 0){

			double epsilon;
			for(int i = 0; i < number_of_regions; i++){
				if (fgets(str,MAXLEN,fp) != NULL){

					//read in arguemnts for next roi operation
					argV = utility::parse(str,6);
					i_origin = atoi(argV[0]);
					j_origin = atoi(argV[1]);
					rows = atoi(argV[2]);
					cols = atoi(argV[3]);
					epsilon = atof(argV[4]);

					//initialize roi
					Region roi(i_origin,j_origin,rows,cols);

					//perform modification on src image
					utility::optimalThresholding(src,roi,epsilon);
				}
			}
			//output final image
			name += "_opt.pgm";	//operation signature
			src.save(name.c_str());
		} 

	}
	
	fclose(fp);

	return 0;
}
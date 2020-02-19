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
		else if(op.compare("opt") == 0){

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

		//optimal Linear Stretching //------------------------------------------------------------------------
		else if(op.compare("ols") == 0){
			
			vector<Region> R;
			double epsilon;
			image bg, bg2, fg, fg2, binarized;
			string filename;
			
			//dummy images to rewritten
			bg.copyImage(src);
			fg.copyImage(src);
			binarized.copyImage(src);

			//create region vector
			for(int i = 0; i < number_of_regions; i++){
				if (fgets(str,MAXLEN,fp) != NULL){
					//read in arguemnts for next roi operation
					argV = utility::parse(str,6);
					i_origin = atoi(argV[0]);
					j_origin = atoi(argV[1]);
					rows = atoi(argV[2]);
					cols = atoi(argV[3]);
					epsilon = atof(argV[4]);

					//save each region for later operations
					Region roi(i_origin,j_origin,rows,cols);
					R.push_back(roi);
					//save binarized image for pixel classification
					utility::optimalThresholding(binarized,roi,epsilon);

				}
			}
			//write backgound before
			Image_Statistics ist_bg = utility::backgound(bg,binarized,R);
			filename = name + "_bkg.pgm";
			bg.save(filename.c_str());
			//write foreground before
			Image_Statistics ist_fg = utility::foreground(fg,binarized,R);
			filename = name + "_obj.pgm";
			fg.save(filename.c_str());
			//apply linear stretching to bg and fg
			for (int i = 0; i < number_of_regions; i++){
				utility::linearHistogramStretching(bg,R[i],ist_bg.getMin(),ist_bg.getMax());
				utility::linearHistogramStretching(fg,R[i],ist_fg.getMin(),ist_fg.getMax());
			}
			//write linear stretched to file
			filename = name + "_bkg_lhs.pgm";
			bg.save(filename.c_str());
			filename = name + "_obj_lhs.pgm";
			fg.save(filename.c_str());
			// combine images into one and write to file
			utility::combine(src,binarized,bg,fg,R);
			filename = name + "_ols.pgm";
			src.save(filename.c_str());
		}

		//Color Histogram Stretching //------------------------------------------------------------------------
		else if(op.compare("chs") == 0){
			int a, b;
			string rgb;
			for(int i = 0; i < number_of_regions; i++){
				if (fgets(str,MAXLEN,fp) != NULL){
					//read in arguemnts for next roi operation
					argV = utility::parse(str,7);
					i_origin = atoi(argV[0]);
					j_origin = atoi(argV[1]);
					rows = atoi(argV[2]);
					cols = atoi(argV[3]);
					rgb = string(argV[4]);
					a = atoi(argV[5]);
					b = atoi(argV[6]);
					

					image* ip = &src;
					//initialize roi
					Region roi(i_origin,j_origin,rows,cols);
					
					if(rgb.compare("r") == 0){
						cout << 'r' << endl;
						Color_Image_Statistics red(ip,roi,RED);
						red.writeHistogramToFile(name + "_red_hist" + to_string(i+1) +"_src.pgm");
						red = utility::colorHistogramStretching(src,roi,RED,a,b);
						red.writeHistogramToFile(name + "_red_hist" + to_string(i+1) + ".pgm");
					}

					else if(rgb.compare("g") == 0){
						cout << 'g' << endl;
						Color_Image_Statistics green(ip,roi,GREEN);
						green.writeHistogramToFile(name + "_green_hist" + to_string(i+1) +"_src.pgm");
						green = utility::colorHistogramStretching(src,roi,GREEN,a,b);
						green.writeHistogramToFile(name + "_green_hist" + to_string(i+1) + ".pgm");
					}

					else if(rgb.compare("b") == 0){
						cout << 'b' << endl;
						Color_Image_Statistics blue(ip,roi,BLUE);
						blue.writeHistogramToFile(name + "_blue_hist" + to_string(i+1) +"_src.pgm");
						blue = utility::colorHistogramStretching(src,roi,BLUE,a,b);
						blue.writeHistogramToFile(name + "_blue_hist" + to_string(i+1) + ".pgm");
					}

					else if(rgb.compare("*") == 0){
						utility::colorHistogramStretching(src,roi,RED,a,b);
						utility::colorHistogramStretching(src,roi,GREEN,a,b);
						utility::colorHistogramStretching(src,roi,BLUE,a,b);
					}

				}
			}
			string filename = name + "_chs.ppm";
			src.save(filename.c_str());
		}

		//Operation not valid //------------------------------------------------------------------------
		else{
			cout << "Invalid opcode \"" << op << "\"" << endl;
		}

	}
	
	fclose(fp);

	return 0;
}
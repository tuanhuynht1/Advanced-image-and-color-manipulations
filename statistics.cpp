#include "statistics.h"

#define MAXRGB 255
#define MINRGB 0

Image_Statistics::Image_Statistics(image* src, Region roi){
    //initialize region and image for this statistics object
    img = src; 
    region = roi;
    histogram.reserve(256); // 0 - 255
    //initialize size of pixel map based on size of region
    vector<vector<int>> temp(region.ilen, vector<int>(region.jlen));
    pixel_map = temp;

    //iterate through each pixel in the roi of src image and populate map by offset to region origin
    for(int i = 0; i < region.ilen; i++){
        for(int j = 0; j < region.jlen; j++){
            pixel_map[i][j] = img->getPixel(i + region.i0, j + region.j0);
            cout << pixel_map[i][j] << " ";
        }
        cout << endl;
    }
}
#include "statistics.h"

#define MAXRGB 255
#define MINRGB 0
#define HISTO_SIZE 256

Image_Statistics::Image_Statistics(image* src, Region roi){
    //initialize region and image for this statistics object
    img = src; 
    region = roi;
    //resize region if out of bounds of image
    if (region.ilim > img->getNumberOfRows()){
        region.ilim = img->getNumberOfRows();
        region.ilen = region.ilim - region.i0;
    }
    if (region.jlim > img->getNumberOfColumns()){
        region.jlim = img->getNumberOfColumns();
        region.jlen = region.jlim - region.j0;
    }

    //initialize size of pixel map based on size of region
    vector<vector<int>> temp1(region.ilen, vector<int>(region.jlen));
    pixel_map = temp1;

    //initialize histogram with zeros
    vector<int> temp2(HISTO_SIZE,0);   // 0 - 255 
    histogram = temp2;

    //iterate through each pixel in the roi of src image and populate map by offset to region origin
    for(int i = 0; i < region.ilen; i++){
        for(int j = 0; j < region.jlen; j++){
            pixel_map[i][j] = img->getPixel(i + region.i0, j + region.j0);
            int value = pixel_map[i][j];
            // cout << value << " ";
            histogram[value]++; //increment frequency of that value
        }
        // cout << endl;
    }
    //iterate through histogram to find mode
    int highest = histogram[0];
    mode = 0;
    for(int i = 1; i < HISTO_SIZE; i++){
        if(histogram[i] > highest){
            highest = histogram[i];
            mode = i;
        }
    }
    cout << mode << endl;

}

int Image_Statistics::pixel(int i, int j){
    if ( i >= region.ilim || j >= region.jlim || i < region.i0 || j < region.j0){
        return -1;  //out of bounds
    }
    return pixel_map[i - region.i0][j - region.j0];
}

void Image_Statistics::writeHistogramToFile(){
    image output(HISTO_SIZE,HISTO_SIZE);

    for(int j = 0; j < HISTO_SIZE; j++){
        int count = histogram[j];
        for(int i  = HISTO_SIZE - 1; i > HISTO_SIZE-1 - count; i--){
            output.setPixel(i,j,MAXRGB);
        }
    }

    output.save("test_hist.pgm");
}
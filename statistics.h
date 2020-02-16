#ifndef STATISTICS_H
#define STATISTICS_H

#include "image.h"

class Image_Statistics{
    public:

    image* img;
    Region region;
    vector<vector<int>> pixel_map;
    vector<int> histogram;

    Image_Statistics(image* src, Region roi);
    int pixel(int i, int j);
    void writeHistogramToFile();

};






#endif
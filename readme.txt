Project 2
Due on 02/24 @ 10:00 AM.

You will need to add these functions to your project: (all operations should be only in the ROIs)

[4 points] Histogram modification
    Grey level histogram stretching, stretch intensities between a and b to 0 and 255
    [Intensity range of original image] -> [Intensity range of stretched image]
    [0,a]->0, [a,b]->[0,255], [b,255]->255
    Apply histogram stretching in up to three ROIs
    Output the histograms before and after the procedure.
    Generate a 256 x 256 image for the histogram. x axis is the intentsity and y axis is #pixel.
    Normalize #pixel from [0,max #pixel] to [0,255]

[3 points] Optimal Thresholding on Gray-level images:
    Implement "Optimal Thresholding Algorithm". Threshold will be updated in each iteration
    Apply optimal thresholding in up to three ROIs (black and white in the ROIs and gray outside)
    The initial threshold is the mean in the ROI

[3 points] Combining image analysis operations
    The operation should be in the ROIs (up to three ROIs)
    Performing Optimal Thresholding within ROI. You will have two regions (Foreground and Background)
    Apply Histogram Stretching to Background and Foreground separately
    Combine histogram stretched Background and Foreground into one image
    The histogram stretching input [a,b] is [min_intensity,max_intensity] in each region (Backgrond/Foreground)

[2 extra points] Color image processing:
    Apply histogram stretching on R, G, and B three channels individually
    Apply histogram stretching on R, G, and B three channels together
    ** Your procedure should support upto three ROIs.

Make sure that you have complete report for this assignment (not just few comments).
     Include input and output images (use several gray level images).
     Discuss performance of histogram processing on grey level images.
     Discuss performance of the thresholding algorithm.
     Discuss performance of combined algorithm.
     Discuss color image processing and its performance. 

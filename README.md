# Image_noises_and_filters

Bluring techniques are applied to reduce image noise. Bluring can be done using convolutional kernek i.e taking a 3X3 matrix , passing it over the images and doing operations and calculating the value for image matrix.

Kernel convolution is the base of mean blur , gaussian blur and edge detection. In kernel convolution we take a small grid of kernel and passing it over the whole image we transform the image.

There are 3 types of blurring technique mostly used in suppressing the noise in image.
 1. Mean Blur: all the values in the kernel are 1. It is more like average the selected pixel with the neighbour pixel.
 2. Gaussian Blur: More controlled and edge preserving than mean blur. Stores the weak edges as well. The kernel for a gaussian blur is:-
    [1,2,1
     2,4,2
     1,2,1] 
 3. Median filter: Best used to reduce salt-pepper noise. Simillar to mean filter, but instead of replacing the value with the mean value of neighbouring pixel,first,the     median is calculated bu first sorting all the pixel values from the surrounding neighborhood into numerical order and then replacing the pixel being considered with     the middle pixel value.(f the neighborhood under consideration contains an even number of pixels, the average of the two middle pixel values is used)

#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// Objects
	Mat original_img, filtered_img;

	// Load image from disk
	original_img = imread("../Imagenes/01_Practicas_1-3/03_ImagenRuidoGaussiano.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!original_img.data){
		cout << "error loading image" << endl;
		return 1;
	}

	// Noise reduction by average of the neighbours determined by the mask
	blur(original_img, filtered_img, Size(3, 3));

	// Gaussian sigma values. The mask dimensions must be square (3x3, 9x9, ...)
	//int sigma_x = 0;
	//int sigma_y = 0;
	//GaussianBlur(original_img, filtered_img, Size(9, 9), sigma_x, sigma_y);
	
	// Median size parameter must be odd and possitive (1, 3, 5, ...)
	//int size = 5;
	//medianBlur(original_img, filtered_img, size);
	
	// Windows for all the images
	namedWindow("Original picture", CV_WINDOW_AUTOSIZE);
	namedWindow("Filtered picture", CV_WINDOW_AUTOSIZE);
	
	// Show image in the name of the window
	imshow("Original picture", original_img);
	imshow("Filtered picture", filtered_img);
	
	// Function for show the image in ms.
	waitKey(0);

	// Free memory
	original_img.release();
	filtered_img.release();
	destroyAllWindows();
	// End of the program
	return 0;
}


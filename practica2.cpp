#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void print_matrix_values(Mat src);

int main(int argc, char* argv[])
{
	// Objects
	Mat original_img;

	// Load image from disk
	original_img = imread("../Imagenes/01_Practicas_1-3/04_Imagenlena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!original_img.data){
		cout << "error loading image" << endl;
		return 1;
	}

	// Objects
	Mat filtered_img(original_img.size(), CV_16SC1);
	Mat show_filtered_img_X(original_img.size(), CV_8UC1);
	Mat show_filtered_img_Y(original_img.size(), CV_8UC1);
	
	// Sobel edge detector:
	//	Gx first order
	//  Gy none
	//	Mask 3x3
	Sobel(original_img, filtered_img, CV_16SC1, 1, 0, 3);
	// Convert to 8 unsigned bit
	filtered_img.convertTo(show_filtered_img_X, CV_8UC1);

	// Sobel edge detector:
	//	Gx first order
	//  Gy none
	//	Mask 3x3
	Sobel(original_img, filtered_img, CV_16SC1, 0, 1, 3);
	// Convert to 8 unsigned bit
	filtered_img.convertTo(show_filtered_img_Y, CV_8UC1);

	// Windows for all the images
	namedWindow("Original picture", CV_WINDOW_AUTOSIZE);
	namedWindow("Filtered picture X", CV_WINDOW_AUTOSIZE);
	namedWindow("Filtered picture Y", CV_WINDOW_AUTOSIZE);

	// Show image in the name of the window
	imshow("Original picture", original_img);
	imshow("Filtered picture X", show_filtered_img_X);
	imshow("Filtered picture Y", show_filtered_img_Y);

	// Function for show the image in ms.
	waitKey(0);

	// Free memory
	original_img.release();
	filtered_img.release();
	show_filtered_img_X.release();
	show_filtered_img_Y.release();
	destroyAllWindows();
	// End of the program
	return 0;
}
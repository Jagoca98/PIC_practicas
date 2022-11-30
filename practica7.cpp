// 
//
#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// Objects
	Mat original_img;
	// Load image from disk
	original_img = imread("../Imagenes/03_Practicas_6-8/04_building.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!original_img.data){
		cout << "error loading image" << endl;
		return 1;
	}
	
	// Canny: 2:1 3x3
	int low_threshold = 50;
	int high_threshold = low_threshold * 4;
	int kernel_size = 3;

	Mat filtered_img(original_img.size(), original_img.type());
	Mat img_color;

	Canny(original_img, filtered_img, low_threshold, high_threshold, kernel_size);
	cvtColor(filtered_img, img_color, COLOR_GRAY2BGR);

	// Hough transform (Standard)
	vector<Vec2f> lines;
	HoughLines(filtered_img, lines, 1, CV_PI/180, 100, 0, 0 );
	
	for( size_t i = 0; i < MIN(lines.size(),50); i++ )
    	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line(img_color, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    	}

	// Hough transform (Probabilistic)
	/*vector<Vec4i> lines;
    	HoughLinesP(filtered_img, lines, 1, CV_PI/180, 80, 30, 10);
        for( size_t i = 0; i < lines.size(); i++ )
   	{
        	Vec4i l = lines[i];
        	line(img_color, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    	}*/

	// Create window canvas to show image
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	namedWindow("Filtered", CV_WINDOW_AUTOSIZE);
	
	// Show image in the name of the window
	imshow("Original", original_img);
	imshow("Filtered", filtered_img);
	imshow("Hough", img_color);
	// Function for show the image in ms.
	// 0 means wait until keyboard is pressed
	waitKey(0);

	// Free memory
	original_img.release();
	filtered_img.release();
	img_color.release();

	destroyAllWindows();
	// End of the program
	return 0;
}


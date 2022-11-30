#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	// Objects
	Mat original01, original02, original03, original04, original05;
	Mat colorCanvas;
	
	// Load image from disk
	original01 = imread("../Imagenes/02_Practicas_4-5/Square05.png", CV_LOAD_IMAGE_GRAYSCALE);
	original02 = imread("../Imagenes/02_Practicas_4-5/Square02.png", CV_LOAD_IMAGE_GRAYSCALE);
	original03 = imread("../Imagenes/02_Practicas_4-5/Square04.png", CV_LOAD_IMAGE_GRAYSCALE);
	original04 = imread("../Imagenes/02_Practicas_4-5/Square01.png", CV_LOAD_IMAGE_GRAYSCALE);
	original05 = imread("../Imagenes/02_Practicas_4-5/Square03.png", CV_LOAD_IMAGE_GRAYSCALE);
	colorCanvas= imread("../Imagenes/02_Practicas_4-5/Square05.png", CV_LOAD_IMAGE_COLOR);

	if (!original01.data || !original02.data || !original03.data 
		|| !original04.data || !original05.data)
	{
		cout << "error loading images" << endl;
		system("pause");
		return 1;
	}

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> cornersA, cornersB;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false; // cornerMinEigenVal then
	double k = 0.04;
	int maxCorners = 4;

	/// Apply corner detection
	goodFeaturesToTrack(original01,
						cornersA,
						maxCorners,
						qualityLevel,
						minDistance,
						Mat(),
						blockSize,
						useHarrisDetector,
						k);

	// status: return the detected corners
	vector<uchar> status;
	// error: return the confidence of the detection
	vector<float> error;
	// play with different sizes and levels
	int winsize = 11;
	int maxlvl = 5;

	// Pyramidal Lucas Kanade optical flow
	calcOpticalFlowPyrLK(original01, original02, cornersA, cornersB, status, error,
		Size(winsize, winsize), maxlvl);
	
	/// Draw corners detected
	int radius = 2;
	cout << "Number of cornersA detected: " << cornersA.size() << endl;
	cout << "Optical Flow corners detected: " << cornersB.size() << endl;

	// the size of cornersA and cornersB is the same even if not detected
	for (int i = 0; i < cornersA.size(); i++)
	{
		circle(colorCanvas, cornersA[i], radius, Scalar(255, 0, 0), -1, 8, 0);
		circle(colorCanvas, cornersB[i], radius, Scalar(0, 255, 0), -1, 8, 0);
		cout << "status: " << (int)status[i];
		cout << " error: " << error[i];
		cout << endl;
		line(colorCanvas, cornersA[i], cornersB[i], Scalar(0, 0, 255));
	}
	
	// Windows for all the images
	namedWindow("ColorCanvas", CV_WINDOW_AUTOSIZE);

	// Show image in the name of the window
	imshow("ColorCanvas", colorCanvas);

	// Function for show the image in ms.
	waitKey(0);

	// Free memory
	original01.release();
	original02.release();
	original03.release();
	original04.release();
	original05.release();
	colorCanvas.release();
	destroyAllWindows();
	// End of the program
	return 0;
}
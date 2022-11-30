// 
//
#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int MinMax(long* Histograma)
{
	float HistogramaAux[256];
	int i,maximo1,maximo2,minimo;
   
	maximo1=0;
	for(i=1;i<256;++i){
		if(Histograma[maximo1]<Histograma[i]){
		maximo1=i;
		}
	}
	for(i=0;i<256;++i){
		HistogramaAux[i]= Histograma[i]*abs(i-maximo1);
	}

	maximo2=0;
	for(i=1;i<256;++i){
		if(HistogramaAux[maximo2]<HistogramaAux[i]){
			maximo2=i;
		}
	}
	cout << "Maximo1 " << maximo1 << " Maximo2 " << maximo2 << endl;		
	
	if(maximo1<maximo2){
		minimo=maximo1;
		for(i=minimo+1;i<maximo2;++i)
			if(Histograma[i]<Histograma[minimo]) minimo=i;
    	}
	else{
		minimo=maximo2;
		for(i=minimo+1;i<maximo1;++i){
			if(Histograma[i]<Histograma[minimo]){ 
				minimo=i;
			}

		}
    	}
	cout << "Minimo " << minimo << endl;
	return (minimo);
}


int main(int argc, char* argv[])
{
	
	// Objects
	Mat img_src;
	long hist_vector[256];
	int threshold_value;
	
	// Load image from disk
	img_src = imread("../Imagenes/03_Practicas_6-8/01_thresholding1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	if (!img_src.data){
		cout << "error loading image" << endl;
		return 1;
	}

	// Calculate histogram
	Mat hist;
	// Establish the number of bins
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	
	calcHist(&img_src, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);
	
	// Plot histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(hist,hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	
	/// Draw 
	hist_vector[0] = 0;
	for (int i = 1; i < histSize; i++)
	{
		hist_vector[i] = hist.at<float>(i);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}


	// Create image for thresholded image
	Mat im_thresholded(img_src.size(), CV_8UC1);
	threshold_value = MinMax(hist_vector);
	threshold(img_src, im_thresholded, threshold_value, 255,THRESH_BINARY);
	line(histImage, Point(bin_w*threshold_value, 0),Point(bin_w*threshold_value, 400),Scalar(0, 255, 0), 2, 8, 0);
	
	// Create window canvas to show image
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
	namedWindow("Thresholded", CV_WINDOW_AUTOSIZE);
	
	// Show image in the name of the window
	imshow("original", img_src);
	imshow("Histogram", histImage);
	imshow("Thresholded", im_thresholded);
	// Function for show the image in ms.
	// 0 means wait until keyboard is pressed
	waitKey(0);

	// Free memory

	img_src.release();
	histImage.release();
	im_thresholded.release();
	destroyWindow("original");
	// End of the program
	return 0;
}


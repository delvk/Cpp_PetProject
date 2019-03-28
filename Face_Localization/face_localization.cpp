// CPP program to detects face in a video 

// Include required header files from OpenCV directory 
#include "opencv2/objdetect.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/core/types_c.h"
#include "opencv2/face.hpp"
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace cv;
using namespace cv::face;


// Function for Face Detection 
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale);
string cascadeName;

int main(int argc, const char** argv)
{
	// VideoCapture class for playing video for which faces to be detected 
	VideoCapture capture;
	Mat frame, image;

	// PreDefined trained XML classifiers with facial features 
	CascadeClassifier cascade;
	double scale = 1;

	// Change path before execution  
	cascade.load("D:/Work/My_Project/Cpp_PetProject/opencv/opencv_build/install/include/opencv2/data/haarcascades/haarcascade_frontalface_default.xml");
	
	/*Mat gray=imread(test_path, 3);
	detectAndDraw(gray, cascade, nestedCascade, scale);*/
	 //Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 

	cout << "Face Detection Started...." << endl;
	
	// WHAT DO YOU WANT ME TO DO
	int what = 1;
	if (what == 0) {
		capture.open(0);
		if (capture.isOpened())
		{
			// Capture frames from video and detect faces 
			while (1)
			{
				capture >> frame;
				if (frame.empty())
					break;
				Mat frame1 = frame.clone();
				detectAndDraw(frame1, cascade, scale);
				char c = (char)waitKey(10);

				// Press q to exit from window 
				if (c == 27 || c == 'q' || c == 'Q')
					break;
			}
		}
		else
			cout << "Could not Open Camera";
	}
	else {
		string test_path = "./Test/test1.jpg";
		Mat gray=imread(test_path, 3);
		detectAndDraw(gray, cascade, scale);
	}

	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 
	
	double fx = 1 / scale;

	// Resize the Grayscale Image 
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	//equalizeHist(smallImg, smallImg);

	cascade.detectMultiScale(smallImg, faces, 1.33, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	
	// This code help you decide image scale, your welcome :))
	
	//double var = 1.1;
	//double best_suit = 0;
	//int temp = 0;

	//for (int i = 0; i < 1000; i++) {
	//	var += 0.01;
	//	cascade.detectMultiScale(smallImg, faces, var, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	//	if (faces.size() == 17) {
	//		temp = faces.size();
	//		break;
	//	}
	//	else {
	//		if (abs(18 - faces.size()) < abs(18 - temp)) {
	//			best_suit = var;
	//			temp = faces.size();
	//		}
	//	}
	//}
	//cout << "Var: " << var << endl;
	//cout << "Count: " << temp<< endl;
	//system("pause");

	for (size_t i = 0; i < faces.size(); i++)
	{
		Mat smallImgROI;
		smallImgROI = smallImg(faces[i]);
		resize(smallImgROI, smallImgROI, Size(180, 200));
		//hello=model->predict(smallImgROI);
		Rect r = faces[i];
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 255, 0); // Color for Drawing tool 
		double aspect_ratio = (double)r.width / r.height;
		rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
		cvPoint(cvRound((r.x + r.width - 1)*scale),
		cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);
		//imshow("result", smallImgROI);
	}
	imshow("result", img);
	cout << "Count: " << faces.size() << endl;
	waitKey(0);
}
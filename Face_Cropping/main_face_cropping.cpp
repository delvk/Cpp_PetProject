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

#include <string>
#include <windows.h>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace cv;
using namespace cv::face;

// Function for Face Detection 
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale, string &name, int &idx);
string cascadeName;

int main(int argc, const char** argv)
{	
	Mat frame, image;
	CascadeClassifier cascade;
	double scale = 1;
	// PreDefined trained XML classifiers with facial features 
	cascade.load("D:/Work/My_Project/Cpp_PetProject/opencv/opencv_build/install/include/opencv2/data/haarcascades_cuda/haarcascade_frontalface_default.xml");
	//path for folder contain images
	string folder_path = "./images";
	string name = "minhtri";
	int idx = 0;
	for (const auto & entry : filesystem::recursive_directory_iterator(folder_path)) {
		if (filesystem::is_directory(entry.path())) continue;
		Mat gray = imread(entry.path().string());
		cout << "sieze:" << gray.size() << endl;
		detectAndDraw(gray, cascade, scale, name, idx);
		idx++;
	}
	
	//Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 	
	system("pause");
	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale, string &name, int &idx)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;
	Mat img_crop;
	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 

	double fx = 1 / scale;

	// Resize the Grayscale Image 
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	//equalizeHist(smallImg, smallImg);

	// Detect faces of different sizes using cascade classifier 
	cascade.detectMultiScale(smallImg, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(40, 40));
	//Draw retangle around the faces 
	for (size_t i = 0; i < faces.size(); i++)
	{
		Mat smallImgROI;
		smallImgROI = smallImg(faces[i]);
		Rect r = faces[i];
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 255, 0); // Color for Drawing tool 
		double aspect_ratio = (double)r.width / r.height;
		/*rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
			cvPoint(cvRound((r.x + r.width - 1)*scale),
				cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);*/
		img_crop = img(r);
		resize(img_crop, img_crop, Size(180, 200));
	}
	
	//// Show Processed Image with detected faces 
	
	vector<int> compression_params;
	compression_params.push_back(100);
	compression_params.push_back(9);
	string filename = name + "/" + name + "." + to_string(idx) + ".jpg";
	try {
		imwrite(filename, img_crop, compression_params);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return ;
	}
	
	//cout << "ket qua la: " << ex[id] << endl;
}
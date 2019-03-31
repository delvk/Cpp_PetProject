#ifndef _OPENCV_HEADER_
#define _OPENCV_HEADER_
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <fstream>
using namespace cv;
using namespace cv::face;
using namespace std;
enum Algorithm {

	EIGENFACES = 1,

	FISHERFACES = 2,

	LBPHFACES = 3
};

static bool Use_EigenFaceRecognizer(vector<Mat> &images, vector<int> &labels);
static bool Use_FisherFaceRecognizer(vector<Mat> &images, vector<int> &labels);
static bool Use_LBPHFaceRecognizer(vector<Mat> &images, vector<int> &labels);
static Mat norm_0_255(InputArray _src);
static void read_csv(string& filename, vector<Mat>& images, vector<string>& names, vector<int>& labels, char separator);
static bool checkUserEnter();
static bool checkUserEnter(int &attemp_number);
#endif

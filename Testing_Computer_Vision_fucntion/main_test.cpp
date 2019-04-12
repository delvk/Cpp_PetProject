#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main() {
	Mat image = imread("image.jpg", 3);
	cvtColor(image, image, COLOR_BGR2GRAY);
	Size size = Size(11, 11);
	GaussianBlur(image, image, size, 2, 2, BORDER_REFLECT101);
	imshow("tesing", image);

	waitKey(0);
	return 0;
}
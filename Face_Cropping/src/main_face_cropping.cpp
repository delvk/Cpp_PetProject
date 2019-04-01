#include "face_regconition.hpp"
// Function for Face Detection 
void detectAndCrop(Mat& img, CascadeClassifier& cascade, double scale, string &name, int &idx);
string cascadeName;

int main(int argc, const char** argv)
{	
	//Initial Variable
	Mat frame, image;
	CascadeClassifier cascade;
	double scale = 1;
	// PreDefined trained XML classifiers with facial features 
	cascade.load("D:/Work/My_Project/Cpp_PetProject/opencv/opencv_build/install/include/opencv2/data/haarcascades_cuda/haarcascade_frontalface_default.xml");
	//path for folder contain images
	string folder_path = "images";
	string name = "output/quocbao";
	int idx = 0;
	//CreateFolder
	if (CreateDirectory(name.c_str(), NULL))
	{
		cout << "Created folder output "<< name << endl;
	}
	else
	{
		// Failed to create directory.
		cout << "Can't create folder output " << name << endl;
	}

	for (const auto & entry : filesystem::recursive_directory_iterator(folder_path)) {
		if (filesystem::is_directory(entry.path())) continue;
		Mat gray = imread(entry.path().string());
		cout << "sieze:" << gray.size() << endl;
		detectAndCrop(gray, cascade, scale, name, idx);
		idx++;
	}
	system("pause");
	return 0;
}

void detectAndCrop(Mat& img, CascadeClassifier& cascade, double scale, string &name, int &idx)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;
	Mat img_crop;
	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 

	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	cascade.detectMultiScale(smallImg, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(40, 40));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Mat smallImgROI;
		smallImgROI = smallImg(faces[i]);
		Rect r = faces[i];
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 255, 0); // Color for Drawing tool 
		double aspect_ratio = (double)r.width / r.height;
		img_crop = img(r);
		resize(img_crop, img_crop, Size(180, 200));
	}
	vector<int> compression_params;
	compression_params.push_back(100);
	compression_params.push_back(9);
	string filename = name + "." + to_string(idx) + ".jpg";
	cout << filename << endl;
	try {
		imwrite(filename, img_crop, compression_params);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return ;
	}
}
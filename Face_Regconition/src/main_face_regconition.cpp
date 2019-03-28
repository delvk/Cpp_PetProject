#include "face_regconition.hpp"
#include "func_face_regcontion.cpp"
int main() {
	string path_training_set = "D:/Work/My_Project/Cpp_PetProject/Data_Preparation/Data_Output/training_set.csv";
	string output_folder = "output";
	// These vectors hold the images and corresponding labels.
	vector<Mat> images;
	vector<string> names;
	vector<int> labels;
	// Read in the data. This can fail if no valid
	// input filename is given.
	try {
		read_csv(path_training_set, images, names, labels);
	}
	catch (const cv::Exception& e) {
		cerr << "Error opening file \"" << path_training_set << "\". Reason: " << e.msg << endl;
		// nothing more we can do
		system("pause");
	}
	// Quit if there are not enough images for this demo.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
	}
	//size 180x200;
	bool ok = true;
	for (int i = 0; i < images.size(); i++) {
		if (images[i].size().empty()) {
			cout << "Test Errror: " << images[i] << endl;
			ok = false;
		}
	}
	if (!ok) {
		cout << "Sai biet kich thuoc ma tran trong tap du lieu, xin thu lai voi tap du lieu khac" << endl;
		system("pause");
		return -1;
	}

	/* create output folder */
	if (CreateDirectory(output_folder.c_str(), NULL))
	{
		cout << "Created folders output!!!" << endl;
	}
	else
	{
		// Failed to create directory.
		cout << "Can't create folder Output" << endl;
	}

	/*---TRAINING---*/
	int what = LBPHFACES;

	cout << "Ban da chon giai thuat so " << what << endl;

	switch (what)
	{
		case EIGENFACES:
		{
			if (Use_EigenFaceRecognizer(images, labels)) cout << "Success" << endl;
			else cout << "Failed" << endl;
			break;
		}
		case FISHERFACES:
		{
			if (Use_FisherFaceRecognizer(images, labels)) cout << "Success" << endl;
			else cout << "Failed" << endl;
			break;
		}
		case LBPHFACES:
		{
			if (Use_LBPHFaceRecognizer(images, labels)) cout << "Success" << endl;
			else cout << "Failed" << endl;
			break;
		}
		default: {
			cout << "khong co giai thuat nao duoc chon, ket thuc chuong trinh" << endl;
			break;
		}
	}
	// Check for valid command line arguments, print usage
	// if no arguments were given.

	system("pause");
	return 0;
}

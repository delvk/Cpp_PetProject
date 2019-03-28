#include "../Face_Regconition/header/face_regconition.hpp"
#include "../Face_Regconition/src/func_face_regcontion.cpp"

int main(int argc, const char *argv[]) {
	int what = LBPHFACES;
	string file_model = "../Face_Regconition/output/";
	//start reading
	cout << "Reading model..." << endl;
	Ptr<FaceRecognizer> model;
	switch (what)
	{
		case EIGENFACES: {
			file_model += "eigen_face_model.yml";
			cout << "Using default input path: " << file_model << endl;
			model = EigenFaceRecognizer::create();
			break;
		}
		case FISHERFACES: {
			file_model += "fisher_face_model.yml";
			cout << "Using default input path: " << file_model << endl;
			model = FisherFaceRecognizer::create();
			break;
		}
		case LBPHFACES: {
			file_model += "LBPH_face_model.yml";
			cout << "Using default input path: " << file_model << endl;
			model = LBPHFaceRecognizer::create();
			break;
		}
		default: {
			cout << "Khong giai thuat nao duoc chon" << endl;
			system("pause");
			return 1;
		}
	}
	//Reading it
	model->read(file_model);
	if (model->empty()) {
		cout << "Model load khong thanh cong, dung chuong trinh " << endl;
		system("pause");
		return 0;
	}
	cout << "Load model successful" << endl;

	/* Loading test case */
	vector<Mat> testSample;
	vector<string> testName;
	vector<int> testLabel;
	try {
		string fn = "D:/Work/My_Project/Cpp_PetProject/Data_Preparation/Data_Output/testing_set.csv";
		read_csv(fn, testSample, testName, testLabel);
	}
	catch (const cv::Exception& e) {
		cerr << "Error opening file \""  << "\". Reason: " << e.msg << endl;
		// nothing more we can do
		system("pause");
	}

	//CHECK ERROR MATRICES SIZE
	for (int i = 0; i < testSample.size(); i++) {
		if (testSample[i].size().empty()) cout << "Test Errror: " << testLabel[i] << endl;
	}

	// vecto predict
	vector<int> predicted_label;
	vector<double> predicted_confidence;
	string check = "";

	//set threshold
	model->setThreshold(1000);

	for (int i = 0; i < testLabel.size(); i++){
		int temp1=-1; double temp2=0.0;
		model->predict(testSample[i],temp1,temp2);
		predicted_label.push_back(temp1);
		predicted_confidence.push_back(temp2);
		vector<int>::iterator it = find(testLabel.begin(), testLabel.end(), predicted_label[i]);
		if (predicted_label[i] != testLabel[i]) check = "*";
		else check = "";
		cout << check << "predict: " << predicted_label[i] << " | " << testLabel[i]<<" -- "<< predicted_confidence[i] << endl;
	}
	model->clear();
	system("pause");
	return 0;
}
// CPP program to detects face in a video 
// Include required header files from OpenCV directory 
#include "opencv2/objdetect.hpp" 
#include "opencv2/core/types_c.h"
#include "face_regconition.hpp"
#include "func_face_regcontion.hpp"
// Function for Face Detection 
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale, Ptr<FaceRecognizer> &model, string *);
string cascadeName, nestedCascadeName;

int main(int argc, const char** argv)
{
	//Initial Variable
	string frontal_face_detect_path = "D:/Work/My_Project/Cpp_PetProject/opencv/opencv_build/install/include/opencv2/data/haarcascades/haarcascade_frontalface_default.xml";

	string model_face_regconition_path = "D:/Work/My_Project/Cpp_PetProject/Face_Regconition/output/LBPH_face_model.yml";

	VideoCapture capture;// VideoCapture class for playing video for which faces to be detected
	Mat frame, image;

	CascadeClassifier cascade; // PreDefined trained XML classifiers with facial features 
	// Load classifiers from "opencv/data/haarcascades" directory 
	cascade.load(frontal_face_detect_path);
	
	double scale = 1;

	cout << "usage: " << argv[0] << endl;
	cout << "<frontal_face_detect_path> <model_face_regconition_path>" << endl;
	cout << "\n----------------------------------------------------------\n" << endl;
	if (argc == 1) {
		cout << "No other arguments other than default application name, using default value (Y/N)?" << endl;
	}
	else if (argc == 2) {
		frontal_face_detect_path = string(argv[1]);
		cout << "You only input frontal_face_detect_path, is this okay (Y/N) ?" << endl;
	}
	else if (argc == 3) {
		frontal_face_detect_path = string(argv[1]);
		model_face_regconition_path = string(argv[2]);
		cout << "Is this okay (Y/N) ?" << endl;
	}
	else exit(1);
	cout << "- PreDefined trained XML classifiers path: " << frontal_face_detect_path << endl;
	cout << "- Pretrained face regconizer model: " << model_face_regconition_path << endl;
	if (!checkUserEnter()) {
		cout << "Well, BYE " << endl;
		cin.get();
		return 0;
	}
	Ptr<FaceRecognizer> model;
	int what = userChooseAlg();
	switch (what)
	{
	case EIGENFACES: {
		model = EigenFaceRecognizer::create();
		break;
	}
	case FISHERFACES: {
		model = FisherFaceRecognizer::create();
		break;
	}
	case LBPHFACES: {
		model = LBPHFaceRecognizer::create();
		break;
	}
	default:
		cout << "I don't know this algorithm, bye" << endl;
		cin.get();
		return 0;
	}
	//read model
	cout << "Reading model" << endl;
	
	string path = model_face_regconition_path;
	model->read(path);
	model->setThreshold(30);
	if (model->empty()) {
		cout << "Loading fail" << endl;
		system("pause");
		return 0;
	}
	cout << "Load model successful" << endl;

	/*Loading dataset_id*/
	vector<Data> data;
	string path_dataset = "D:/Work/My_Project/Cpp_PetProject/Data_Preparation/Data_Output/dataset_id.csv";
	if (!read_dataset_id(path_dataset, data)) {
		cout << "There are line(s) couldn't be read correctly" << endl;
	}
	/* This help access data quicker*/
	string *names = new string[data.size()];
	for (int i = 0; i < data.size(); i++) {
		names[i] = getName(i, data);
	}

	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 

	cout << "Face Detection Started...." << endl;
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
			detectAndDraw(frame1, cascade, scale,model, names);
			char c = (char)waitKey(10);

			// Press q to exit from window 
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Could not Open Camera";

	delete[] names;
	cin.get();
	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	double scale,
	Ptr<FaceRecognizer> &model,
	string *names

)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 

	double fx = 1 / scale;

	// Resize the Grayscale Image 
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	//equalizeHist(smallImg, smallImg);
	//imshow("test", smallImg);
	// Detect faces of different sizes using cascade classifier 
	cascade.detectMultiScale(smallImg, faces, 1.33,
		2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	//Draw retangle around the faces 
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
		//Print prediction
		int z = model->predict(smallImgROI);
		if (z == -1) cout << "Unknow" << endl;
		else cout << names[z] << endl;
	}
	// Show Processed Image with detected faces 
	imshow("result", img);
}
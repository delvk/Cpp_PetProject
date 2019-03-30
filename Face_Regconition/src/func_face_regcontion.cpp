/*
 *   See <http://www.opensource.org/licenses/bsd-license>
 */
#include "../header/face_regconition.hpp"
static bool Use_EigenFaceRecognizer(vector<Mat> &images, vector<int> &labels) {
	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels);
	string filename = "output/eigen_face_model.yml";
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE | FileStorage::MEMORY);
	model->save(filename);
	fs.release();
	bool temp = !model.empty();
	if (temp) model->clear();
	return temp;
};
static bool Use_FisherFaceRecognizer(vector<Mat> &images, vector<int> &labels) {
	Ptr<FaceRecognizer> model = FisherFaceRecognizer::create();
	model->train(images, labels);
	string filename = "output/fisher_face_model.yml";
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE | FileStorage::MEMORY);
	model->save(filename);
	fs.release();
	cout << "Luu file "<< filename<< " thanh cmn cong roi" << endl;
	bool temp = !model.empty();
	if (temp) model->clear();
	return temp;
};

static bool Use_LBPHFaceRecognizer(vector<Mat> &images, vector<int> &labels) {
	Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
	model->train(images, labels);
	string filename = "output/LBPH_face_model.yml";
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE | FileStorage::MEMORY);
	model->save(filename);
	fs.release();
	cout << "Luu file " << filename << " thanh cmn cong roi" << endl;
	bool temp = !model.empty();
	if (temp) model->clear();
	return temp;
};


static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	// Create and return normalized image:
	Mat dst;
	switch (src.channels()) {
	case 1:
		cv::cvtColor(src, dst, CV_8UC1);
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::cvtColor(src, dst, CV_8UC3);
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}

static void read_csv(const string& filename, vector<Mat>& images, vector<string>& names, vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(Error::StsBadArg, error_message);
	}
	string line, path, classlabel, className;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, className, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			//XU LI ANH MAU BGR SANG GRAY
			Mat gray;
			cvtColor(imread(path,3), gray, COLOR_BGR2GRAY);
			resize(gray, gray, Size(180, 200));
			images.push_back(gray);
			names.push_back(className);
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
	cout << "Reading " << images.size() << " training examples successful" << endl;
}
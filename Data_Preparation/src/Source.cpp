#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <fstream>
using namespace std;

//initial argument
string train_folder = "Data_Training";
string vali_folder = "Data_Validation";
string test_folder = "Data_Testing";
string output_folder = "Data_Output";
string data_input_path = "database/faces94/female";
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}
int count_size(const filesystem::path path) {
	int temp = 0;
	for (const auto & entry : filesystem::directory_iterator(path)) {
		temp++;
	}
	return temp;
}

void write_csv(const char* input, const char* output) {
	int id = -1;
	string name = "";
	int size_each_example = 0;
	int size_train=0,
		size_test=0,
		size_vali=0;
	int train_idx = 0;
	string s_path = "";

	ofstream file_train, file_test, file_dataset;

	string path1 = string(output) + "/training_set.csv";
	file_train.open(path1);

	string path2 = string(output) + "/testing_set.csv";
	file_test.open(path2);

	string path3 = string(output) + "/dataset_id.csv";
	file_dataset.open(path3);

	for (const auto & entry : filesystem::recursive_directory_iterator(input)) {
		if (filesystem::is_directory(entry.path())) {
			if (id < 0)
			{
				//mac dinh tinh size tu thu muc dau tien no tim dc
				size_each_example = count_size(entry.path());
				//chia so training va test
				size_train = size_each_example * 0.8;
				size_test = size_each_example * 0.2;
				cout << "size train: " << size_train << endl;
				cout << "size test: " << size_test << endl;
			}
			id++;
			train_idx = 0; //reset bien train_idx moi khi qua mot thu muc moi
			name = entry.path().filename().string();
			cout << "new: " << id << "; " << name << endl;
			file_dataset <<id<<";"<<name << endl;
		}
		else 
		{ 
			s_path = filesystem::absolute(entry).string();
			findAndReplaceAll(s_path, "\\", "/"); //chuan hoa path
			if (train_idx < size_train) { //nho hon so phai training thi ghi vao file training
				cout << "training: " << s_path << ";" << name << ";" << id << endl;
				file_train << s_path << ";" << name << ";" << id << endl;

			}
			else { //nguoc lai thi ghi testing
				cout << "testing: " << s_path << ";" << name << ";" << id << endl;
				file_test << s_path << ";" << name << ";" << id << endl;
			}
			train_idx++;
		}
	}
	file_train.close();
	file_test.close();
}
void write_train(ofstream *outfile, const string path) {
	for (const auto & entry : filesystem::directory_iterator(path)) {
		if (filesystem::is_directory(entry.path())) {
			write_train(outfile, entry.path().string());
		}
		else {
			////outfile << entry.path() << endl;
			*outfile << entry.path().string() << ";" << entry.path().parent_path().filename().string() << endl;
		}
	}
}
void write_csv() {
	//write training_set.csv
	ofstream outfile;
	string path = output_folder + "/training_set.csv";
	outfile.open(path);
	write_train(&outfile, train_folder);
	outfile.close();

	//write testing_set.csv
	path = output_folder + "/testing_set.csv";
	outfile.open(path);
	write_train(&outfile, test_folder);
	outfile.close();
}
void testing() {
	for (auto& p : filesystem::recursive_directory_iterator(data_input_path.c_str()))
		std::cout << p.path() << '\n';
}
int main(int argc, const char *argv[]) {
	// Check for valid command line arguments, print usage
	// if no arguments were given.
	//message
	cout << "usage: " << argv[0] << endl;
	cout << "option: 2 for training - testing, 3 for training, testing, validation" << endl;
	cout << "database_path" << endl;
	if (argc < 2) {
		argv[1] = "3";
	}
	if (argc < 3) {
		argv[2] = data_input_path.c_str();
		cout << "No input database path, using default ./database" << endl;
	}
	if (argc < 4) {
		argv[3] = output_folder.c_str();
		if (CreateDirectory(output_folder.c_str(), NULL))
		{
			cout << "Created folders Output!!!" << endl;
		}
		else
		{
			// Failed to create directory.
			cout << "Can't create folder Output" << endl;
		}
	}

	//start copying - Prepare data
	write_csv(argv[2], argv[3]);

	//write data to csv file in output directory

	//write_csv();

	system("pause");
	return 0;
}

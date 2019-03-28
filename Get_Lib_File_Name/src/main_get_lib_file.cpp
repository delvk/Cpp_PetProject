#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
void duyet_dir(ofstream *outfile,const string path, unsigned int &id_number) {
	cout << "Input folder: " << path << endl;
	for (const auto & entry : filesystem::directory_iterator(path)) {
		if (filesystem::is_directory(entry.path())) {
			//duyet_dir(outfile, entry.path().string(),id_number);
			id_number++;
		}
		else {
			////outfile << entry.path() << endl;
			string temp = entry.path().filename().string();
			temp= temp.substr(temp.find_last_of(".") + 1);
			if (temp == "lib" or temp =="Lib")
			*outfile << entry.path().filename().string()<<";"<<endl;
		}
	}
}
int main()
{
	//initial variable
	ofstream outfile;
	string path = ".";
	unsigned int id_number = 0;
	outfile.open("rsc/lib.txt");
	duyet_dir(&outfile, path, id_number);
	outfile.close();
	cout << "Output file: " << "rsc/lib.txt" << endl;
	system("pause");
	return 0;
}
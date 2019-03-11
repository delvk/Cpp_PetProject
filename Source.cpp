//#include <iostream>
//#include <string>
//#include <filesystem>
//#include <fstream>
//using namespace std;
//int main()
//{
//	ofstream file("ListNhacUpdateThuongXuyen.txt");
//	if (file.is_open())
//	{
//		for (const auto & entry : std::filesystem::directory_iterator("W:\Temp")) {
//			cout << entry.path().u8string() << endl;
//			/*string full_name = entry.path().string();
//			cout << full_name.substr(2, -1) << endl;*/
//			//cout << "."<<endl;
//		}
//		file.close();
//		cout << "Ghi ten tat ca file thanh cong !!!" << endl;
//	}
//	else cout << "Unable to open file ListNhacUpdateThuongXuyen.txt";
//	system("pause");
//	return 0;
//}

#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>

using namespace boost::filesystem;
using namespace std;

void iterateDirs(const path &dir_path, vector<path> &dir, FILE *fLog, int child_th)
{
	
	//std::wofstream myfile(L"example.txt");
	if (exists(dir_path) && fLog != NULL)
	{
		directory_iterator end_itr;
		WCHAR newLine[] = L"\r\n";
		size_t num = sizeof(WCHAR);
		WCHAR* tab = (WCHAR*)malloc(child_th);
		wcscpy(tab, L"");
		if (child_th != 0) {
			
			for (int i = 0; i < child_th; i++) {
				wcscat(tab, L"\t");
			}			
		}
		for (directory_iterator itr(dir_path); itr != end_itr; ++itr) {
			fwrite(tab, sizeof(WCHAR), wcslen(tab), fLog);
			if ((is_directory(itr->status()))) {
				fwrite(L"* ", sizeof(WCHAR), 2, fLog);
				fwrite(itr->path().filename().wstring().c_str(), num, wcslen(itr->path().filename().wstring().c_str()), fLog);
				fwrite(newLine, sizeof(WCHAR), wcslen(newLine), fLog);
				
				iterateDirs(itr->path(), dir, fLog, ++child_th);
				
				dir.push_back(itr->path());
			}
			else if (is_regular_file(itr->status())) {
				//WCHAR wcError[] = itr->path().filename().wstring().c_str();
				//wcout << itr->path().filename().wstring().c_str();
				/*_cputws(itr->path().filename().wstring().c_str());
				_cputws(L"\n");*/
				fwrite(L"- ", sizeof(WCHAR), 2, fLog);
				fwrite(itr->path().filename().wstring().c_str(), num, wcslen(itr->path().filename().wstring().c_str()), fLog);
				fwrite(newLine, sizeof(WCHAR), wcslen(newLine), fLog);
				//dir.push_back(itr->path());
				//cout << dir.size() << endl;
			}
		}
	}
	child_th--;
}

int main() {
	FILE* fLog;
	vector<path> dirs;
	fLog = _wfopen(L"ListNhacUpdateThuongXuyen.txt", L"wb");
	iterateDirs(".", dirs,fLog,0);
	fclose(fLog);
	///
	cout << endl;
	cout << "File ki hieu '-'" << endl;
	cout << "Thu muc ki hieu '*'" << endl;
	cout << endl;

	system("pause");
	return 0;
}
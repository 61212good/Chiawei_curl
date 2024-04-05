//g++ -o img_download_demo img_download.cpp & img_download_demo.exe
#include <iostream>
#include <string>
#include <dirent.h>
#include <sstream>
#include <vector>
using namespace std;

string fileNamestring;

// 函数用于分割字符串
std::vector<std::string> splitString(const std::string& input, char delimiter) {
	std::vector<std::string> tokens;
	std::istringstream stream(input);
	std::string token;

	while (std::getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

int getfileName(string getfilePath) {
	// 用实际目录路径替换 "your_directory_path_here"
	std::string directoryPath = getfilePath;

	// 打开目录
	DIR* directory = opendir(directoryPath.c_str());

	// 检查目录是否成功打开
	if (directory != nullptr) {
		// 读取目录中的条目
		dirent* entry;
		while ((entry = readdir(directory)) != nullptr) {
			// 获取当前条目的文件名
			std::string fileName = entry->d_name;

			// 忽略当前目录和上级目录
			if (fileName != "." && fileName != ".." 
				&& fileName != "img_download_demo.exe" && fileName != "img_download.exe"
				&& fileName != "img_download.cpp" 
				&& fileName != "tmp" && fileName != "tmp_2") {
				// 打印文件名
				// std::cout << "fileName: " << fileName << std::endl;
				fileNamestring = fileName;
			}
		}

		// 关闭目录
		closedir(directory);
	} else {
		std::cerr << "Path not found!" << std::endl;
	}

	if(fileNamestring == ""){
		return -1;
	}

	return 0 ;

}

int existPath(string searchPath) {
	std::string directoryPath = searchPath;
	// 打开目录
	DIR* directory = opendir(directoryPath.c_str());
	// 检查目录是否成功打开
	if (directory != nullptr) {
		// 关闭目录
		closedir(directory);
		return 0;
	} else {
		return -1;
	}
}

int main() {
	string curl_cmd_1="curl -O \"";
	string curl_cmd_3="\"";
	string stringcin_selectpath;
	string stringcin_imgurl;
	string instruction_1="mkdir tmp";
	string instruction_2="mkdir tmp_2";
	string instruction_3;
	string instruction_4;
	string img_fileName;

	if(existPath("./tmp/") != 0){
		system(instruction_1.c_str());
	}
	if(existPath("./tmp_2/") != 0){
		system(instruction_2.c_str());
	}

	do{
		cout<<""<<endl;
		cout<<"//------------------------------------------------//"<<endl;
		cout<<"//Path List:"<<endl;
		cout<<"//( 1 ) ./tmp/"<<endl;
		cout<<"//( 2 ) ./tmp_2/"<<endl;
		cout<<"//------------------------------------------------//"<<endl;
		cout<<""<<endl;
		cout<<"Select save Path: "<<endl;
		cin>>stringcin_selectpath;
		if(!(stringcin_selectpath=="1" || stringcin_selectpath=="2")){
			cout<<"Exit"<<endl;
			break;
		}

		do{
			cout<<"Enter img url: "<<endl;
			cin>>stringcin_imgurl;
			if(stringcin_imgurl=="0"){
				cout<<"Exit"<<endl;
				break;
			}

			instruction_3 = curl_cmd_1+stringcin_imgurl+curl_cmd_3;
			system(instruction_3.c_str());

			if(getfileName("./") != 0){
				cout<<"getfileName Error!"<<endl;
				break;
			}

			img_fileName = fileNamestring;

			if(stringcin_selectpath=="1"){
				instruction_4 = "move "+img_fileName+" ./tmp/"+img_fileName;
			}else if(stringcin_selectpath=="2"){
				instruction_4 = "move "+img_fileName+" ./tmp_2/"+img_fileName;
			}

			system(instruction_4.c_str());

		}while(stringcin_imgurl!="0");

	}while(stringcin_selectpath!="0");

	return 0;
}
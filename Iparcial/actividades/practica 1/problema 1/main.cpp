#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void load(string path);

int main(int argc, char** argv) {
	
	load("words.txt");
	
	return 0;
}

void load(string path) {
	fstream file;
	file.open(path.c_str(), ios::in);
	
	string line;
	int cases = 0;
	char *split;
	vector<string> output;
	
	if (file.fail()) 
		cout << "Error opening file " << endl;
	else {
		file >> cases;
		getline(file, line);
		while (getline(file, line)) {
			split = strtok(&line[0], " ");
			vector<string> dict;
			while (split) {
				dict.push_back(split);				
				split = strtok(NULL, " ");
			}
			
			getline(file, line);
			vector<string> word;
			split = strtok(&line[0], " ");
			while (split) {
				word.push_back(split);
				split = strtok(NULL, " ");
			}	
			
			for (int i = 0; i < word.size(); i++) {	
				string c_word = word[i];
				for (int j = 0; j < dict.size(); j++) {
					string c_word_dict = dict[j];
					if (c_word.size() == c_word_dict.size()) {
						if (c_word[0] == c_word_dict[0] && c_word[c_word.size() - 1] == c_word_dict[c_word_dict.size() - 1]) {
							output.push_back(c_word_dict);
							break;
						}
					}		
				}			
			}
			
			for (int i = 0; i < output.size(); i++) {	
				cout << output[i] << ' ';
			}
			output.clear();
			cout << endl;
		}
	}
}

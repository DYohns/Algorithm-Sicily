#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void GetMainID(const string str, string &mainID) {
	size_t found = str.find_last_of(" ");
	mainID = str.substr(found + 1);
}


bool CompareMain_ID(string a, string b) {
	string mainID_a, mainID_b;
	GetMainID(a, mainID_a);
	GetMainID(b, mainID_b);
	return mainID_a < mainID_b;
}

int main() {
	map<string, string> map_IP2ID;
	vector<string> vec_output;
	int num;
	string str_ID, str_ip, str_output;
	while (cin >> num && num) {
		map_IP2ID.clear();
		vec_output.clear();
		for (int i = 0; i < num; i++) {
			cin >> str_ID >> str_ip;
			int isSame = 0;
			if (map_IP2ID.count(str_ip)) {
				str_output = str_ID + " is the MaJia of " + map_IP2ID[str_ip];
				vec_output.push_back(str_output);
			}
			else {
				map_IP2ID.insert(pair<string, string>(str_ip, str_ID));
			}
		}
		sort(vec_output.begin(), vec_output.end(), CompareMain_ID);
		for (int i = 0; i < vec_output.size(); i++) {
			cout << vec_output[i] << endl;
		}
		cout << endl;
	}

	return 0;
}
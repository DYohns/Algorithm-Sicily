#include <iostream>
#include <vector>
#include <string>
using namespace std;

void ChangeStrand(const string origin_strand, string & result_strand) {
	result_strand = origin_strand;
	for (int i = 0; i < result_strand.length(); i++) {
		switch (result_strand[i]) {
		case 'A': result_strand[i] = 'T'; break;
		case 'T': result_strand[i] = 'A'; break;
		case 'G': result_strand[i] = 'C'; break;
		case 'C': result_strand[i] = 'G'; break;
		}
	}
}

int isMatch(vector<string> &vec_sStrand, const string str_sStrand) {
	int index = -1;
	string re_strand;
	ChangeStrand(str_sStrand, re_strand);
	for (int i = 0; i < vec_sStrand.size(); i++) {
		if (vec_sStrand[i] == re_strand) {
			index = i;
			break;
		}
	}
	return index;
}

int main() {
	int caseNum, sStrandNum, dStrandNum;
	vector<string> vec_sStrand;
	string sStrand;
	cin >> caseNum;
	while (caseNum--) {
		dStrandNum = 0;
		cin >> sStrandNum;
		vec_sStrand.clear();
		while (sStrandNum--) {
			cin >> sStrand;
			int index = isMatch(vec_sStrand, sStrand);
			if (index != -1) {
				dStrandNum++;
				vec_sStrand.erase(vec_sStrand.begin() + index);
			}
			else
			{
				vec_sStrand.push_back(sStrand);
			}
		}
		cout << dStrandNum << endl;
	}
}
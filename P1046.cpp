#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


struct quarter {
	int period;
	int end;
	double average;
	int index;
	int all;
};

bool SortFn(quarter a, quarter b) {
	if (fabs(a.average - b.average) > 0.000000001) {
		return a.average > b.average;
	}
	if (a.period != b.period) {
		return a.period > b.period;
	}
	return a.end < b.end;

}

int main() {
	int caseNum;
	int a, b, c, temp;
	vector<int> vec_planes;
	vector<quarter> vec_allSequence;
	cin >> caseNum;
	for (int n = 0; n < caseNum; n++) {
		vec_allSequence.clear();
		vec_planes.clear();
		cin >> a >> b >> c;
		for (int i = 0; i < a; i++) {
			cin >> temp;
			vec_planes.push_back(temp);
		}

		for (int i = 0; i < vec_planes.size() - c + 1; i++) {
			int all = 0;
			for (int j = i; j < vec_planes.size(); j++) {
				all += vec_planes[j];
				int period = j - i + 1;
				if (period >= c) {
					quarter q;
					q.all = all;
					q.average = (double)all / period;
					q.index = i;
					q.period = period;
					q.end = j;
					vec_allSequence.push_back(q);
				}
			}
		}

		sort(vec_allSequence.begin(), vec_allSequence.end(), SortFn);
		cout << "Result for run " << n + 1 << ":" << endl;
		for (int i = 0; i < b && i < vec_allSequence.size(); i++) {
			cout << vec_allSequence[i].index + 1
				<< "-"
				<< vec_allSequence[i].end + 1 << endl;

		}
		/*	cout << "------------------------------------------------------------------" << endl;
			for (int i = 0; i < vec_allSequence.size(); i++) {
				cout << "index: " << vec_allSequence[i].index << endl;
				cout << "period: " << vec_allSequence[i].period << endl;
				cout << "all: " << vec_allSequence[i].all << endl;
				cout << "average: " << vec_allSequence[i].average << endl;
			}*/


	}
	return 0;
}
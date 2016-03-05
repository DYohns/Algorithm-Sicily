/*
 ID: 1007 - To and Fro
 DESC: ºÚµ•Ã‚
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
	int columnNum;
	string message;
	while (cin >> columnNum && columnNum) {
		cin >> message;
		for (int i = 0; i < columnNum; i++) {
			int j = i;
			int temp = i * 2 + 1;
			while (j < message.length()) {
				temp = columnNum * 2 - temp;
				cout << message[j];
				j += temp;
			}
		}
		cout << endl;
	}


	return 0;
}
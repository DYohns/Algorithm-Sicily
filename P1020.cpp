#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void GetRepresentation(const int b, char *longInteger, int &rep) {
	int i = 1;
	int lI_length = strlen(longInteger);
	int remainder = 0;
	int current;
	for (int i = 0; i < lI_length; i++) {
		current = (int)longInteger[i] - 48;
		remainder = (remainder * 10 + current) % b;
	}
	rep = remainder;
}

void GetOutputString(const int num, int * rep) {
	cout << "(";
	for (int i = 0; i < num; i++) {
		if (i == 0) {
			cout << rep[i];
			continue;
		}
		cout << "," << rep[i];
	}
	cout << ")" << endl;
}

int main()
{
	int caseNum, bNum, b[1000], rep[1000];
	char longInteger[401];
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++) {
		cin >> bNum;
		for (int j = 0; j < bNum; j++) {
			cin >> b[j];
		}
		cin >> longInteger;
		for (int j = 0; j < bNum; j++) {
			GetRepresentation(b[j], longInteger, rep[j]);
		}
		GetOutputString(bNum, rep);
	}
	return 0;
}
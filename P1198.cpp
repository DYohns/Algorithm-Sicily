/*
�������ַ������ϣ������������е�Ԫ����ϳ��µ��ַ�������������ֵ�����ó���С���е��ַ���
����{"a", "kt", "kta"}����С�ַ���Ϊ"aktakt"
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool SortCondition(string a, string b) {
	return a + b < b + a;
}

int main() {
	int caseNum, pieceNum;
	string piece;
	vector<string> vec_pieces;
	cin >> caseNum;
	while (caseNum--) {
		vec_pieces.clear();
		cin >> pieceNum;
		while (pieceNum--) {
			cin >> piece;
			vec_pieces.push_back(piece);
		}
		sort(vec_pieces.begin(), vec_pieces.end(), SortCondition);
		for (int i = 0; i < vec_pieces.size(); i++) {
			cout << vec_pieces[i];
		}
		cout << endl;
	}

}
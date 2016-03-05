/*
	ID: 1150-简单魔板
	desc: 简单魔方的移动
	tips: 采用queue存储
*/

#include <iostream>
#include <string>
#include <queue>
using namespace std;
struct RubicsCube {
	int x[4];
	int y[4];
	string step;
};

bool IsMatch(int x[], int y[], RubicsCube rc) {
	bool isMatch = true;
	for (int i = 0; i < 4; i++) {
		if (x[i] != rc.x[i] || y[i] != rc.y[i]) {
			isMatch = false;
			break;
		}
	}
	return isMatch;
}

void CubeOperation(RubicsCube ori_rc, RubicsCube& new_rc, char op) {
	switch (op) {
	case 'A':
		for (int i = 0; i < 4; i++) {
			new_rc.x[i] = ori_rc.y[i];
			new_rc.y[i] = ori_rc.x[i];
		}
		new_rc.step = ori_rc.step + "A";
		break;
	case 'B':
		int index;
		for (int i = 0; i < 4; i++) {
			index = (i + 1) % 4;
			new_rc.x[index] = ori_rc.x[i];
			new_rc.y[index] = ori_rc.y[i];
		}
		new_rc.step = ori_rc.step + "B";
		break;
	case 'C':
		new_rc.x[0] = ori_rc.x[0];
		new_rc.y[0] = ori_rc.y[0];
		new_rc.x[3] = ori_rc.x[3];
		new_rc.y[3] = ori_rc.y[3];

		new_rc.x[1] = ori_rc.y[1];
		new_rc.x[2] = ori_rc.x[1];
		new_rc.y[1] = ori_rc.y[2];
		new_rc.y[2] = ori_rc.x[2];

		new_rc.step = ori_rc.step + "C";
		break;
	}
}


int main() {
	int length;
	int x[4], y[4];
	queue<RubicsCube> que_rubicsCube;
	while (cin >> length && length != -1) {
		while (!que_rubicsCube.empty()) {
			que_rubicsCube.pop();
		}

		RubicsCube *first_rc = new RubicsCube();
		for (int i = 0; i < 4; i++) {
			first_rc->x[i] = i + 1;
			first_rc->y[i] = 8 - i;
		}
		que_rubicsCube.push(*first_rc);

		for (int i = 0; i < 4; i++) {
			cin >> x[i];
		}
		for (int i = 0; i < 4; i++) {
			cin >> y[i];
		}
		bool isMatch = false;
		while(true) {
			RubicsCube rc = que_rubicsCube.front();
			if (rc.step.length() > length) {
				break;
			}
			// A operation
			RubicsCube *new_rc = new RubicsCube();
			CubeOperation(rc, *new_rc, 'A');
			que_rubicsCube.push(*new_rc);
			if (IsMatch(x, y, *new_rc) == true) {
				isMatch = true;
				break;
			}

			// B operation
			new_rc = new RubicsCube();
			CubeOperation(rc, *new_rc, 'B');
			que_rubicsCube.push(*new_rc);
			if (IsMatch(x, y, *new_rc) == true) {
				isMatch = true;
				break;
			}
			// C operation
			new_rc = new RubicsCube();
			CubeOperation(rc, *new_rc, 'C');
			que_rubicsCube.push(*new_rc);
			if (IsMatch(x, y, *new_rc) == true) {
				isMatch = true;
				break;
			}
			que_rubicsCube.pop();
		}
		if (isMatch == true) {
			RubicsCube rc = que_rubicsCube.back();
			cout << rc.step.length() << " ";
			cout << rc.step << endl;
		}
		else {
			cout << "-1" << endl;
		}
	}

	return 0;
}
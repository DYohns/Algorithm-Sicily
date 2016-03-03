#include <iostream>
#include <vector>
using namespace std;
int main() {
	int num, a, b;
	vector<int> circle;
	vector<int> stack;
	while (cin >> num && num) {
		stack.clear();
		circle.clear();
		circle.resize(num * 2);
		int  flag = 0;
		for (int i = 0; i < num; i++) {
			cin >> a >> b;
			circle[a - 1] = i;
			circle[b - 1] = i;
		}
		for (int i = 0; i < circle.size(); i++) {
			if (stack.empty() || circle[i] != stack.back()) {
				stack.push_back(circle[i]);
			}
			else {
				stack.pop_back();
			}
		}
		if (stack.empty()) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}
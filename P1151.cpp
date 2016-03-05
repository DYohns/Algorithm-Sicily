/*
	ID: 1151-魔板
	desc: 简单魔方的移动
	tips: 此题通过主要受到内存大小的限制，实际上魔方排列顺序有限，只有8!=40320种排列方式，不需要对相同的排列方式进行再次变换，所以只需要构造数组isFound[40320]来存储就行了。
		可以采用康托展开，类似哈希一样，可以将数字不同的排列通过康托展开映射到一个数。
		具体过程如下，采用队列queue存放节点，每一次访问队列头部进行ABC操作，操作结果需要通过康托展开在isFound[]中判断是否访问过了，若无，则插入队列尾部，并设置isFound[]的值。
		如此一来，当满足条件即可输出结果。
		康托展开介绍如下：
		https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80

*/

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

//数据结构
struct RubicsCube {
	int value; // 存储状态，如12348765
	string step; // 存储步骤
};

bool IsMatch(const int value, RubicsCube rc) {
	return value == rc.value;
}

// 将int数值按十进制位转换为数组
void Int2Array(int value, int *arr) {
	for (int i = 0; i < 8; i++) {
		arr[7 - i] = value % 10;
		value /= 10;
	}
}

// 将数组转换为十进制int数值
void Array2Int(int *arr, int& value) {
	value = 0;
	for (int i = 0; i < 8; i++) {
		value = value * 10 + arr[i];
	}
}

/*
	康托展开：https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80
	例如，3 5 7 4 1 2 9 6 8 展开为 98884。因为X=2*8!+3*7!+4*6!+2*5!+0*4!+0*3!+2*2!+0*1!+0*0!=98884.
	排列的第一位是3，比3小的数有两个，以这样的数开始的排列有8!个，因此第一项为2*8!
	排列的第二位是5，比5小的数有1、2、3、4，由于3已经出现，因此共有3个比5小的数，这样的排列有7!个，因此第二项为3*7!
	以此类推，直至0*0!
*/
int GetCantor(int value, int* fact) {
	int arr[8];
	Int2Array(value, arr);
	int lowerNum, cantor = 0;
	for (int i = 0; i < 7; i++) {
		lowerNum = 0;
		for (int j = i + 1; j < 8; j++) { // 获取康托展开系数
			if (arr[j] < arr[i]) {
				lowerNum++;
			}
		}
		cantor += lowerNum * fact[i];
	}
	return cantor;
}

// 进行ABC变换操作
void CubeOperation(RubicsCube ori_rc, RubicsCube& new_rc, char op) {
	int arr[8], new_arr[8], newValue;
	Int2Array(ori_rc.value, arr);
	switch (op) {
	case 'A':
		for (int i = 0; i < 4; i++) {
			new_arr[i] = arr[i + 4];
			new_arr[i + 4] = arr[i];
		}
		Array2Int(new_arr, newValue);
		new_rc.value = newValue;
		new_rc.step = ori_rc.step + "A";
		break;
	case 'B':
		for (int i = 0; i < 4; i++) {
			new_arr[i] = arr[(i + 3) % 4];
			new_arr[i + 4] = arr[(i + 3) % 4 + 4];
		}
		Array2Int(new_arr, newValue);
		new_rc.value = newValue;
		new_rc.step = ori_rc.step + "B";
		//cout << new_rc.step << ": " << newValue << endl;
		break;
	case 'C':
		new_arr[0] = arr[0];
		new_arr[1] = arr[5];
		new_arr[2] = arr[1];
		new_arr[3] = arr[3];
		new_arr[4] = arr[4];
		new_arr[5] = arr[6];
		new_arr[6] = arr[2];
		new_arr[7] = arr[7];
		Array2Int(new_arr, newValue);
		new_rc.value = newValue;
		new_rc.step = ori_rc.step + "C";
		//cout << new_rc.step << ": " << newValue << endl;
		break;
	}
}

queue<RubicsCube> que_rubicsCube; // 存放队列
bool isFound[40320]; // 节点访问状态
int main() {
	int length;
	int x[8];
	int value;
	// 预先存储康托展开需要的阶层，7!, 6!, 5!, 4!, 3!, 2!, 1!
	int fact[] = { 5040, 720, 120, 24, 6, 2, 1}; 
	int cantor;
	while (cin >> length && length != -1) {
		bool isMatch = false;
		RubicsCube new_rc;
		RubicsCube first_rc;

		memset(isFound, false, sizeof(isFound));
		while (!que_rubicsCube.empty()) {
			que_rubicsCube.pop();
		}

		first_rc.value = 12348765;
		first_rc.step = "";
		que_rubicsCube.push(first_rc);

		for (int i = 0; i < 8; i++) {
			cin >> x[i];
		}
		Array2Int(x, value);

		if (value == 12348765) { // 若目标和初始状态一样，则直接得出结果
			isMatch = true;
		}

		while (!isMatch) {
			RubicsCube rc = que_rubicsCube.front(); // 取队列头部数据
			if (rc.step.length() == length) { // 若不满足在规定步数内达到目标状态，则退出循环
				break;
			}

			// A operation
			CubeOperation(rc, new_rc, 'A');	// 进行A操作
			cantor = GetCantor(new_rc.value, fact);	// 获得康托展开对应数值
			if (isFound[cantor] == false) { // 若没有访问过，则存入队列尾部，并令isFound为true
				isFound[cantor] = true;
				que_rubicsCube.push(new_rc);
				if (IsMatch(value, new_rc) == true) { // 若匹配到目标状态，则isMatch = true，退出循环
					isMatch = true;
					break;
				}
			}

			// B operation
			CubeOperation(rc, new_rc, 'B');
			cantor = GetCantor(new_rc.value, fact);
			if (isFound[cantor] == false) {
				isFound[cantor] = true;
				que_rubicsCube.push(new_rc);
				if (IsMatch(value, new_rc) == true) {
					isMatch = true;
					break;
				}
			}

			// C operation
			CubeOperation(rc, new_rc, 'C');
			cantor = GetCantor(new_rc.value, fact);
			if (isFound[cantor] == false) {
				isFound[cantor] = true;
				que_rubicsCube.push(new_rc);
				if (IsMatch(value, new_rc) == true) {
					isMatch = true;
					break;
				}
			}
			
			que_rubicsCube.pop();
		}
		if (isMatch == true) { // 匹配到则输出结果
			RubicsCube rc = que_rubicsCube.back();
			cout << rc.step.length() << " ";
			cout << rc.step << endl;
		}
		else {	// 无法在规定步数内得到目标状态
			cout << "-1" << endl;
		}
	}
	return 0;
}
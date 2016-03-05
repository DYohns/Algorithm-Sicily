/*
	ID: 1151-ħ��
	desc: ��ħ�����ƶ�
	tips: ����ͨ����Ҫ�ܵ��ڴ��С�����ƣ�ʵ����ħ������˳�����ޣ�ֻ��8!=40320�����з�ʽ������Ҫ����ͬ�����з�ʽ�����ٴα任������ֻ��Ҫ��������isFound[40320]���洢�����ˡ�
		���Բ��ÿ���չ�������ƹ�ϣһ�������Խ����ֲ�ͬ������ͨ������չ��ӳ�䵽һ������
		����������£����ö���queue��Žڵ㣬ÿһ�η��ʶ���ͷ������ABC���������������Ҫͨ������չ����isFound[]���ж��Ƿ���ʹ��ˣ����ޣ���������β����������isFound[]��ֵ��
		���һ��������������������������
		����չ���������£�
		https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80

*/

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

//���ݽṹ
struct RubicsCube {
	int value; // �洢״̬����12348765
	string step; // �洢����
};

bool IsMatch(const int value, RubicsCube rc) {
	return value == rc.value;
}

// ��int��ֵ��ʮ����λת��Ϊ����
void Int2Array(int value, int *arr) {
	for (int i = 0; i < 8; i++) {
		arr[7 - i] = value % 10;
		value /= 10;
	}
}

// ������ת��Ϊʮ����int��ֵ
void Array2Int(int *arr, int& value) {
	value = 0;
	for (int i = 0; i < 8; i++) {
		value = value * 10 + arr[i];
	}
}

/*
	����չ����https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80
	���磬3 5 7 4 1 2 9 6 8 չ��Ϊ 98884����ΪX=2*8!+3*7!+4*6!+2*5!+0*4!+0*3!+2*2!+0*1!+0*0!=98884.
	���еĵ�һλ��3����3С������������������������ʼ��������8!������˵�һ��Ϊ2*8!
	���еĵڶ�λ��5����5С������1��2��3��4������3�Ѿ����֣���˹���3����5С������������������7!������˵ڶ���Ϊ3*7!
	�Դ����ƣ�ֱ��0*0!
*/
int GetCantor(int value, int* fact) {
	int arr[8];
	Int2Array(value, arr);
	int lowerNum, cantor = 0;
	for (int i = 0; i < 7; i++) {
		lowerNum = 0;
		for (int j = i + 1; j < 8; j++) { // ��ȡ����չ��ϵ��
			if (arr[j] < arr[i]) {
				lowerNum++;
			}
		}
		cantor += lowerNum * fact[i];
	}
	return cantor;
}

// ����ABC�任����
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

queue<RubicsCube> que_rubicsCube; // ��Ŷ���
bool isFound[40320]; // �ڵ����״̬
int main() {
	int length;
	int x[8];
	int value;
	// Ԥ�ȴ洢����չ����Ҫ�Ľײ㣬7!, 6!, 5!, 4!, 3!, 2!, 1!
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

		if (value == 12348765) { // ��Ŀ��ͳ�ʼ״̬һ������ֱ�ӵó����
			isMatch = true;
		}

		while (!isMatch) {
			RubicsCube rc = que_rubicsCube.front(); // ȡ����ͷ������
			if (rc.step.length() == length) { // ���������ڹ涨�����ڴﵽĿ��״̬�����˳�ѭ��
				break;
			}

			// A operation
			CubeOperation(rc, new_rc, 'A');	// ����A����
			cantor = GetCantor(new_rc.value, fact);	// ��ÿ���չ����Ӧ��ֵ
			if (isFound[cantor] == false) { // ��û�з��ʹ�����������β��������isFoundΪtrue
				isFound[cantor] = true;
				que_rubicsCube.push(new_rc);
				if (IsMatch(value, new_rc) == true) { // ��ƥ�䵽Ŀ��״̬����isMatch = true���˳�ѭ��
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
		if (isMatch == true) { // ƥ�䵽��������
			RubicsCube rc = que_rubicsCube.back();
			cout << rc.step.length() << " ";
			cout << rc.step << endl;
		}
		else {	// �޷��ڹ涨�����ڵõ�Ŀ��״̬
			cout << "-1" << endl;
		}
	}
	return 0;
}
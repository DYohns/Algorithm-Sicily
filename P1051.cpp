/*
应用题，计算出distance和MPH，然后取精度即可
*/
#include <iostream>
#include <iomanip>
using namespace std;

double PI = 3.1415927;
int FOOT_PER_MILE = 5280;
int INCH_PER_FOOT = 12;
int MINUTE_PER_HOUR = 60;
int SECOND_PER_MINUTE = 60;


int main() {
	double diameter, se_time;
	int revolution;
	int caseNum = 1;
	while (cin >> diameter >> revolution >> se_time && revolution != 0) {
		double distance;
		double MPH;

		distance = diameter / INCH_PER_FOOT / FOOT_PER_MILE * PI * revolution;
		MPH = distance / se_time * MINUTE_PER_HOUR * SECOND_PER_MINUTE;
		
		cout << setiosflags(ios::fixed);
		cout << setprecision(2);
		
		cout << "Trip #" << caseNum << ": " << distance << " " << MPH << endl;

		caseNum++;
	}


	return 0;
}
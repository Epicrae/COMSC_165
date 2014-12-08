#include<iostream>

using namespace std;

int main() {

	float e = 99.0f;
	float* f = &e;
	
	float a = 9.0f;
	float* b = &a;

	float c = 13.0f;
	float* d = &c;


	cout << (b > d ? "b>d" : "b<d") << endl;
	cout << (b > f ? "b>f" : "b<f") << endl;

	return 0;
}

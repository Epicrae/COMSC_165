#include <iostream>
#include <assert.h>
using namespace std;

int gcf(int, int);

int main(void) {

	cout << "Starting tests." << endl;

	const int num_tests = 5;

	// GCF of a_i and b_i should equal gcf_i
	int a_arr[num_tests]   
		= {55, 196, 201, 2,  9};
	int b_arr[num_tests]   
		= {11, 42,  42,  20, 47};
	int gcf_arr[num_tests] 
		= {11, 14,  3,   2,  1};
	
	// Test each of the cases above
	for (int i = 0; i < num_tests; i++) {
		assert (gcf(a_arr[i], b_arr[i]) == gcf_arr[i]);
		cout << "GCF of " 
			<< a_arr[i] << " and " 
			<< b_arr[i] << " is " 
			<< gcf_arr[i] << endl;
	}

	cout << "All tests passed." << endl;

	int a, b;
	cout << "Enter first number: ";
	cin >> a;

	cout << "Enter second number: ";
	cin >> b;

	cout << "Greatest Common Factor: " << gcf(a, b) << endl;

	return 0;
}

int gcf(int a, int b) {

	// Just for consistent ordering
	if (b > a)
		return gcf(b, a);

	assert (a >= b == true);

	if (b == 0)
		return a;
	else 
		return gcf(b, a%b);

}

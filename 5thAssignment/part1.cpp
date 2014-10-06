#include<iostream>
#include<vector>
using namespace std;

// Takes care of getting non-negative ints from stdin.
int getValidatedInt();

float average(int*, int);
float median(int*, int);
void mode(int*, int, vector<int> &mode);

int main() {

	cout << "How many students were surveyed? ";

	int numStudents = getValidatedInt();

	int* movies = (int*) malloc(sizeof(int) * numStudents);

	for (int i = 0; i < numStudents; i++) {

		cout << "Which movie did student " << i+1 <<  " like? ";
		*(movies + i) = getValidatedInt();
	}

	cout << "Average: " << average(movies, numStudents) << endl;
	cout << "Median: " << median(movies, numStudents) << endl;

	// Vector to hold all possible modes.
	vector<int> modes;
	mode(movies, numStudents, modes);
	
	// Print all modes
	cout << "Mode(s): ";
	if (modes.size() == numStudents)
		cout << "No mode.";
	else
		for (int i = 0; i < modes.size(); i++)
			cout << modes.at(i) << (i < modes.size() - 1 ? "," : ".");
	cout << endl;

	return 0;
}

int getValidatedInt() {

	int temp;
	cin >> temp;

	while (temp < 0) {

		cout << "Number must be positive." << endl;
		cin >> temp;
	}

	return temp;
}

/**
 * Returns the average of the numbers stored in arr. 
 *  If the size is invalid, returns a negative number. 
 */
float average(int* arr, int s) {

	if (s <= 0) throw "Undefined array size.";
	float sum;
	
	for(int i = 0; i < s; i++)
		sum += *(arr + i);
	
	return sum / s; 
}

/**
 * Assumes arr is sorted, and returns the median value.
 * If size is odd, this is the middle value.
 * If size is even, this is the average of the two middle values.
 */ 
float median(int* arr, int s) {
	return s % 2 == 0 ? .5f*(*(arr + s/2 - 1) + *(arr+(s/2))) : *(arr + s/2);
}

// Functions like a quick and small hash table for modes values.
struct mostHolder {
	int value;
	int seenTimes;
};

/** 
 * Returns the value that occurs most often in arr.
 * If there is no mode, returns -1.
 */
void mode(int* arr, int s, vector<int> &vecModes) {

	// Holds each unique number, and records how many times it was seen.
	vector<mostHolder> lookup;

	// Go through the entire array.
	for (int i = 0; i < s; i++) {

		// Is this value already in the table?
		bool found = false;

		// Search the table
		for(int j = 0; j < lookup.size(); j++) {

			// If that value is already in the table..
			if (lookup[j].value == *(arr + i)) {

				// Record that we've seen this value again.
				lookup[j].seenTimes++;
				found = true;
			}
		}

		// This value was not in the table already..
		if (!found) {

			// So we add it.
			mostHolder m;
			m.value = *(arr + i);
			m.seenTimes = 1;
			lookup.push_back(m);
		}
	}
	
	// How many times the most common number is seen.
	int mostTimes = 0;

	// Find the highest number of occurrences - may not be unique.
	for (int i = 0; i < lookup.size(); i++) {
		if (lookup[i].seenTimes > mostTimes)
			mostTimes = lookup[i].seenTimes;
	}

	// Add all of the numbers that tied for being seen the most number of times
	// (may only be one).
	for (int i = 0; i < lookup.size(); i++) {
		if (lookup[i].seenTimes == mostTimes) {
			vecModes.push_back(lookup[i].value);
		}
	}
}

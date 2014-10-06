/*************************************************************************
* Author:      Zack Garza
* Assignment:  Assignment 4 - Searching and Sorting
* Date:        9/18/2014
* Description: 

* Status:      Completed
************************************************************************/
#include<iostream>

using namespace std;

void printArray(int[], int);
int searchFor(int[], int, int);
void sortArray(int[], int);
float getMean(int[], int);
int binarySearch(int[], int, int, int);

int main() {
	
	int numberOfElements = 0;
	
	cout << "Enter number of elements: ";
	cin >> numberOfElements;

	int sizeOfArray = numberOfElements <= 50 ? numberOfElements : 50;
	int elemArray[sizeOfArray];

	cout << "Array of size " << sizeOfArray << " created." << std::endl;

	for(int i = 0; i < numberOfElements && i < 50; i++) {

		cout << "Enter the value of element " << i << ": ";
		cin >> elemArray[i];
	}

	cout << "Array before sorting: ";;
	printArray(elemArray, sizeOfArray);

	sortArray(elemArray, sizeOfArray);
	cout << "Array after sorting: ";
	printArray(elemArray, sizeOfArray);

	int thisNumber;
	cout << "Enter an integer to search for: ";
	cin >> thisNumber;
	
	int foundNumber  = searchFor(elemArray, sizeOfArray, thisNumber);

	cout << (foundNumber != -1  ? 
			"Number found at index " + std::to_string(foundNumber) 
			: "Number not found.") 
			<< " in sorted array. " << std::endl;

	float mean = getMean(elemArray, sizeOfArray);
	cout << "The mean of the items in the list is : " << mean << std::endl;

	return 0;
}

void sortArray(int array[], int aSize) {
	
	int temp;
	bool swapped;

	do {

		swapped = false;

		for(int i = 1; i < aSize; i++) {

			if(array[i-1] > array[i]) {

				swapped = true;
				temp = array[i];
				array[i] = array[i-1];
				array[i-1] = temp;
			}
		}

	} while(swapped);

	return;
}

int searchFor(int arr[], int aSize, int n) {

	cout << "Searching for  " << n << "..." << std::endl;

	return binarySearch(arr, n, 0, aSize-1);
}

int binarySearch(int arr[], int n, int low, int high) {

	while(low < high) {

		unsigned  mid = (high+low) / 2;

		if (arr[mid] > n) {

			high = mid--;

		} else if (arr[mid] < n) {

			low = mid++;

		} else return mid; // Found.
	}

	return -1;
}

float getMean(int array[], int aSize) {

	float total = 0;

	for(int i = 0; i < aSize; i++) {

		total += array[i];
	}

	return (total / aSize);
}

void printArray(int array[], int aSize) {

	cout << "[";
	for(int i = 0; i < aSize; i++) {
		cout << i << (i==aSize-1 ? "]" : ",");
	}
	cout << std::endl;
}


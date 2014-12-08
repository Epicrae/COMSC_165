/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 3, Part 1
 * Date:        8/30/2014
 * Description: 

 * Status:			In Progress
 ************************************************************************/

#include <iostream>
#include <iomanip>

void getTemperatures(int tempArray[], int numTemps) {

	for(int i = 0; i < numTemps; i++) {

		std::cout << "Enter temperate for day " << i+1 << ": ";
		std::cin >> tempArray[i];
	}
}

void sortArray(int tempArray[], int numTemps) {

	bool swap;

	do {

		swap = false;

		for(int i = 1; i < numTemps; i++) {

			if(tempArray[i-1] > tempArray[i]) {

				int temp = tempArray[i-1];
				tempArray[i-1] = tempArray[i];
				tempArray[i] = temp;
				swap = true;
			}
		}
	} while(swap);
}

float averageTemps(int t[], int n) {
	
	int sum = 0;
	for(int i = 0; i < n; i++) {
		sum += t[i];
	}
	return sum / n;
}

int main() {

	std::cout << "How many temperatures are there to input? ";

	int numTemps;
	std::cin >> numTemps;
	// #Todo: Integer validation

	int tempArray[numTemps];

	getTemperatures(tempArray, numTemps);

	sortArray(tempArray, numTemps);

	for(int i = 0; i < numTemps; i++) {
		std::cout << tempArray[i] << std::endl;
	}

	float average = averageTemps(tempArray, numTemps);

	std::cout << "Average temperature: " 
		<< std::fixed << std::setprecision(2)
		<< average << "." << std::endl;

	return 0;
}

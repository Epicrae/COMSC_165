/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 2, Part 3
 * Date:        8/30/2014
 * Description:	Allows entering an arbitrary number of class grades, 
		and calculates the sum, average score, and average letter grade
		of the set of grades. 
 * Status:		Complete
 ************************************************************************/

#include <iostream>
#include <iomanip>

float sumGrades(int numGrades, float* grades) {

	float total = 0.0f;

	for (int i = 0; i < numGrades; i++) {
		total += grades[i];
	}

	return total;
}

float* readGrades(int numGrades) {
 
	float* gradesContainer = new float[numGrades];

	for (int i = 0; i < numGrades; i++) {
		std::cout << "Enter grade number " << i + 1 << ": ";
		std::cin >> gradesContainer[i];
	}
	
	return gradesContainer;
}

void calcAverage(float sum, float numGrades, float &average) {
	
	average = sum / numGrades;
}

char getLetterGrade(float avg) {

	char grade;

	if (avg >= 90.0f) grade = 'A';
	else if (avg >= 80.0f) grade = 'B';
	else if (avg >= 70.0f) grade = 'C';
	else if (avg >= 60.0f) grade = 'D';
	else grade = 'F';

	return grade;
}

void startProgram() {
	
	std::cout << "How many grades are there to input? ";
	int numberOfGrades;
	std::cin >> numberOfGrades;
	
	float* grades = readGrades(numberOfGrades);
	float sum = sumGrades(numberOfGrades, grades);

	float avg = 0.0f;
	calcAverage(sum, numberOfGrades, avg);

	std::cout << "The sum is: " << sum << std::endl;
	std::cout << "The average is: " << avg << std::endl;

	char letterGrade = getLetterGrade(avg);
	std::cout << "The average grade is: " << letterGrade << std::endl;
}
int main() 
{
	startProgram();
    return 0;
}






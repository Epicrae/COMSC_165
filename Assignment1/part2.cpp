/*****************************************************
 * Author:		Zack Garza
 * Assignment:	Assignment 1, Part 2
 * Date:		9/21/2014
 * Description:	
 		Given the number of tellers that have worked over the past three years as input,
 * 		and the number of days they were out sick, computes the total number of tellers and total
 *		number of days missed by all tellers over the 3-year interval.
 * Status:		Complete
 *****************************************************/

#include <iostream>

void startProgram() {

	std::cout << "How many tellers worked at Nation's Bank during the last three years?" << std::endl;
	
	int numberOfTellers;
	std::cin >> numberOfTellers;	
	
	int totalDaysMissed = 0;

	for (int i = 0; i < numberOfTellers; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "How many days was teller " << i+1 << " out suck during year " << j+1 << "?" << std::endl;
			
			int numDays;
			std::cin >> numDays;
			totalDaysMissed += numDays;
		}
	}

	std::cout << "There were " 
		<< numberOfTellers << " tellers out sick for a total of " 
		<< totalDaysMissed << " days during the last three years." << std::endl;
}

int main() {
	
	startProgram();
	return 0;
}

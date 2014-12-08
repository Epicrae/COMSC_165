/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 2, Part 2
 * Date:        8/30/2014
 * Description: 
	Given a distance traveled and time spent, calculates the average speed.
 * Status:		Complete
 ************************************************************************/

#include <iostream>
#include <iomanip>

void calculateMph(float distance, float time, float &mph) {
	mph = distance / time;
}

int main() 
{
	float miles= 0.0f, hours= 0.0f, mph = 0.0f;
	
	std::cout << "How many miles were traveled? ";
	std::cin >> miles;

	std::cout << "How many hours were spent in transit? ";
	std::cin >> hours;

	calculateMph(miles, hours, mph);
	std::cout << "Your average speed was " 
		<< std::fixed << std::setprecision(2) 
		<< mph << " miles per hour. " << std::endl;

    return 0;
}






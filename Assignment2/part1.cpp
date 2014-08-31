/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 2, Part 1
 * Date:        8/30/2014
 * Description: 
 	Takes two floating point numbers via standard input, and 
	swaps their values.

 * Status:		Complete
 ************************************************************************/

#include <iostream>
using namespace std;

void readNumber(float &number)
{
	cin >> number;
}

void swap(float &first, float &second)
{
	float temp = first;
	first = second;
	second = temp;
}

int main ()
{
	float first = 0, second = 0;
	
	cout << "What is the first number? ";
    readNumber(first);

	cout << "What is the second number? ";
	readNumber(second);

	cout << "Your numbers before swapping are: " 
		<< first << ", " 
		<< second << endl;

	swap(first, second);	
		
	cout << "Your numbers after swapping are: " 
		<< first << ", " 
		<< second << endl;

    return 0;
}






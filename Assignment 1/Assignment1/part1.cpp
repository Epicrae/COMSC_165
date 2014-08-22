/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 1
 * Date:        8/21/2014
 * Description: 
		A program that performs a survey tally on favorite types
        of beverages. Each person selects a beverage from a list, and
        entering -1 stops the program and performs the tally.
 * Status:		Complete
 ************************************************************************/

#include <iostream>
using namespace std;

void tallyVotes()
{

	// Print the initial menu
    cout << "Beverage choices: "
        << endl << "1: Coffee"
        << endl << "2: Tea"
        << endl << "3: Coke"
        << endl << "4: Orange Juice"
        << endl;

    int numberOfPeople = 0, choice = 0;

    int votes[4] = {0, 0, 0, 0};	// Holds number of votes for each beverage

    while (choice != -1) {	// -1 is the sentinel value that exits the loop

        cout << "Please input the favorite beverage of person #" << (numberOfPeople + 1) 
		<< ": Choose 1, 2, 3, or 4 from the above menu, or -1 to exit the program. " << endl;
        cin >> choice;

        while (choice != -1 && (choice < 1 || choice > 4)) {
            cout << "Invalid selection, please enter a value from 1, 2, 3, or 4, or -1 to exit: ";
            cin >> choice;
        }

        votes[choice-1]++;	// Incremenet vote corresponding to berverage chosen
        numberOfPeople++;	// Indicate one more person has voted
    }
	
	// Display results.
	cout << "The total number of people surveyed is " << numberOfPeople - 1 
		<< ". The results are as follows:" << endl;

	cout << "Beverage number of Votes" << endl
		<< "****************************************" 
        << endl << "1: Coffee: "          << votes[0]
        << endl << "2: Tea: "             << votes[1]
        << endl << "3: Coke: "            << votes[2]
        << endl << "4: Orange Juice: "    << votes[3]
        << endl;
}


int main ()
{
    tallyVotes();
    return 0;
}






/*************************************************************************
 * Author:      Zack Garza
 * Assignment:  Assignment 3, Part 2
 * Date:        8/30/2014
 * Description: 
 *
 * Status:			Completed
 ************************************************************************/
#include <iostream>

using namespace std;

void printBoard(char b[3][3]) {

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			cout << b[i][j];
		}
		cout << endl;
	}
}


bool checkBoard(char b[3][3]) {

	char symbol[2] = { 'X', 'O' };

	for (int sym = 0; sym < 2; sym++) {

		char s = symbol[sym];

		// Check rows and columns
		for(int i = 0; i < 3; i++) {
			if (b[i][0] == s && b[i][1] == s && b[i][2] == s) return true;
			if (b[0][i] == s && b[1][i] == s && b[2][i] == s) return true;
		}

		// Check diags
		if (b[0][0] == s && b[1][1] == s && b[2][2] == s) return true;
		if (b[0][2] == s && b[1][1] == s && b[2][0] == s) return true;
	}
	return false;
}

int main() {

	int moves = 0;
	char board[3][3] = 
	{
		{'*','*','*'},
		{'*','*','*'}, 
		{'*','*','*'}
	};

	bool won = false;
	int player = 0;
	int row, column;
	char cont;
	
	char symbol[2] = { 'X', 'O' };
	while (!won) {
	
		cout << "Player " << player+1 << "'s move." << endl;
		cout << "Symbol that will be used: " << symbol[player] << endl;
		
		cout << "Enter row: ";
		cin >> row;
		
		cout << "Enter column: ";
		cin >> column;
		cout << endl;
		
		board[row][column] = symbol[player];
		moves++;
		won = checkBoard(board);

		printBoard(board);
		
		if (won || moves >= 9) break;
		else player = ++player % 2;
		cout << "----------------------------------------------" << endl;
	}
	
	if (won) {
		cout << "Player " << player+1 << " won!";}
	else {
		cout << "Tie!" << endl;
	}
	return 0;
}

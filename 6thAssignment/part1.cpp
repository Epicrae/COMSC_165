#include<iostream>
using namespace std;

bool isPalindrome(char*, int);

int main() {

	char* s = (char*) malloc(sizeof(char)*50);
	cout << "Enter string to check: ";
	fgets(s, 50, stdin);

	int numChars = strlen(s);
	s = (char*) realloc(s, sizeof(char) * numChars);


	bool check = isPalindrome(s, numChars);
	cout << "Your string is "
		<< (check ? "" : "not ") 
		<< "a palindrome." << endl;

	return 0;
}

bool isPalindrome(char* s, int ssize) {

	// Assume it's true until it's not
	bool isPalindrome = true;

	// Integer division to handle even/odd cases
	int middle = ssize / 2;

	// Copy s into a temp string so it can be sent to lowercase
	char* t = (char*) malloc(sizeof(char)*ssize);
	for(; *s; ++s, ++t) *t = tolower(*s);
	// Reset pointer positions
	s -= ssize; t -= ssize;

	// Only go through half of the loop
	for (int i = 0; i < middle; i++) {
		// Compare symmetric letters. Subtract 1 for null term, 1 for starting count at 0.
		if (*(t+i) != *(t+ssize-i-2)) isPalindrome = false;
	}
	free(t);

	// True, as long as every symmetric letter was equal.
	return isPalindrome;
}

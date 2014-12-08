#include<iostream>
#include<cstring>
using namespace std;

int main() {
	
	char* name1 = (char*) malloc(sizeof(char)*25);
	char* name2 = (char*) malloc(sizeof(char)*25);

	cout << "Enter name 1 (Last Name, First Name): ";
	fgets(name1, 25, stdin);

	// More than 25 chars? Flush the input buffer
	if (*(name1+strlen(name1)-1) != '\n') {
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	}

	cout << "Enter name 2 (Last Name, First Name): ";
	fgets(name2, 25, stdin);

	int cmp = strcmp(name1, name2);

	// Remove trailing newlines (for uniform printing)
	strtok(name1, "\n");
	strtok(name2, "\n");

	char *first, *second;
	if (cmp < 0) {
		// The first name comes before the second name
		first = name1;
		second = name2;
	} else {
		// The second name comes before the first name
		first = name2;
		second = name1;
	}

	cout << "The names you entered, in alphabetical order, are: " << endl;
	cout << first << endl;
	cout << second << endl;
	if (cmp == 0) cout << "The names are the same." << endl;

	return 0;
}

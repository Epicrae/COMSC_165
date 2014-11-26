#include<iostream>
#include<vector>
#include<assert.h>
#include<climits>

#define debug false 

using namespace std;


/* -----------------------Structure:-------------------- */

// Nodes of the linked list. Holds integers.
typedef struct entry {
	
	// Holds this entry's value
	int number;

	// Points to the next element in the list. Null if this
	// node is the last element in the list.
	entry* nextElement;

} entry;


// Invariant: linkedList is always in a sorted state such that the smallest 
// number is first and the largest number is last.
typedef struct linkedList {
	
	// Handles memory allocations for the nodes.
	// Not guaranteed to be in a sorted state.
	vector<entry> contents;
	
	// Points to the entry in 'contents' that is the first node of the list.
	entry* head;

} linkedList;



/* -----------------------General Methods:-------------------- */

// Takes a linkedList and adds a new entry with value 'newNumber'.
// PostCondition: linkedList is sorted and contains and entry with 'newNumber'
void addNumber(linkedList&, int newNumber);

// Takes a linkedList and searches for 'rmNumber'. If it is found, it is
// deleted from the list. 
// PostCondition: linkedList list is sorted and does not contain 'rmNumber'.
bool deleteNumber(linkedList&, int rmNumber);

// Iterates through the entire list, and prints the content of each entry.
// Does not alter the contents of the list.
void displayList(const linkedList&);

// Helper method that pretty-prints a single entry.
void printEntry(const entry*, int);

// Helper method that sorts the list after certain operations
// to guarantee its invariant sortedness.
void sortList(linkedList&);

// Run assertion tests.
void runTests();
/*---------------------------------------------------------------*/


/* -----------------------Search Methods:-------------------- */

// Just get a boolean denoting whether or not searchNumber was found at least once.
bool search(const linkedList&, int searchNumber);

// Get the actual entry. Returns a nullptr if searchNumber is not found.
entry* searchNumber(const linkedList&, int searchNumber, bool internal);
entry* searchNumber(const linkedList&, int searchNumber);
/*---------------------------------------------------------------*/


/*------------------------Helper Functions--------------------*/

// Valid menu choices
enum MENU_CHOICE { ADD, DELETE, DISPLAY, QUIT};

// How many entries are in MENU_CHOICE
int num_options = 4;

// How many times to allow incorrect input before exiting program
int menu_error_chances = 5;

// Convert int input into an entry in the MENU_CHOICE enum
MENU_CHOICE getMenuChoice();

// Route choice to program functionality
void processMenuChoice(const MENU_CHOICE, linkedList&);

// Prompts the user (up to menu_error_chances times) for an integer in 
// the range (min, max]
int getValidatedInt(const int min, const int max);

// Pretty-print menu options to stdout
void print_menu_options();
/*---------------------------------------------------------------*/




/* -----------------------Implementation:-------------------- */


/* -----------------------Publicly Accessible Methods -------*/

// Creates a list and performs several tests.
int main(void) {

	if(debug) runTests();

	MENU_CHOICE choice;
	linkedList* list = new linkedList;
	do 
	{
		choice = getMenuChoice();
		if(debug) cout << "Main: Menu choice was: " << choice+1 << endl;
		processMenuChoice(choice, *list);

	} while (choice != QUIT);

	return 0;

}

void addNumber(linkedList& list, int number) {

	cout << "Adding " << number << " to the linked list." << endl;

	// Create a new entry holding the number
	entry* e = new entry;
	e->number = number;
	e->nextElement = nullptr;

	// Add it into the list, letting vector take care of memory allocation
	list.contents.push_back(*e);

	// If this is the first item going into the list, initialize it
	if (list.head == nullptr) {
		cout << "List was empty. Initializing with new entry." << endl;
		list.head = e;

	// Otherwise, traverse the list, and add this entry at the appropriate point
	} else {
		entry* current = list.head;
		while (current->nextElement != nullptr)
			current = current->nextElement;	
		current->nextElement = e;
	}

	// Ensure the list is always in a sorted state to maintain invariant.
	sortList(list);
}

bool deleteNumber(linkedList& list, int num) {

	if(debug) cout << "Called deleteNumber." << endl;

	// Get the first entry where 'num' occurs
	entry* e = searchNumber(list, num);

	// Return false if it was not found
	if (&e == nullptr) {
		cout << "Number not found in list." << endl; 
		return false;
	}


	entry* current = list.head;

	for (int i = 0; i < list.contents.size() 
			&& list.contents[i].number <= num; i++) {

		// Check if this is the number to be deleted.
		if (list.contents[i].number == num) {

			// Points the previous node's 'next' to this node's 'next'
			// Note - sortedness is guaranteed, we can access nodes 
			// directly by their index. This negates the need to 
			// keep track of the previous node's pointer when 
			// it needs to be changed. This should also handle 
			// the case where this is the last item.
			list.contents[i-1].nextElement = list.contents[i].nextElement;

			// Deallocate this node's memory and remove it from the vector
			list.contents.erase(list.contents.begin() + i);

			return true;
		}
	}
	
	// Node was never found.
	return false;
}


void displayList(const linkedList& list) {

	// Use 1-based indexing for human-readable display
	int index = 1;
	if(debug) cout << "Printing list. " << endl;

	// Make sure the list has at least one item in it
	if (list.head == nullptr) {
		cout << "List is empty." << endl;

	// If so, traverse the list and print each element
	} else {
		entry* current = list.head;

		// Print the first element
		printEntry(current, index);

		// And traverse only as long as there is a next element
		while (current->nextElement != nullptr) {
			current = current->nextElement;
			printEntry(current, ++index);
		}
	}
}

// Use if you just want to know /if/ the number was found
bool search(const linkedList& list, int num) {
	if (debug) cout << "Boolean search function called." << endl;
	return (searchNumber(list, num, true) == nullptr ? false : true);
}

// Use if you need to actually work with the entry if it is found
entry* searchNumber(const linkedList& list, int number) {
	if(debug) cout << "Called searchNumber from an external method." << endl;
	return searchNumber(list, number, false);
}

// Set internal=true to suppress stdout output. Useful for testing.
// For external calls, just use the two-arg searchNumber
entry* searchNumber(const linkedList& list, int number, bool internal) {

	if(debug) cout << "Entry search function called." << endl;

	// Keep track of the index number for pretty-printing
	int index = 1;

	// Start searching at the first item
	entry* current = list.head;

	// Keep track of whether or not number has been found yet
	bool found = false;

	if(!current) {
		if (debug) cout << "Current pointer is null." << endl;
		return nullptr;
	}

	// If the search term is less than the first number, it can't be in the list
	if (number < current->number) {
		if(debug) cout << "Number less than HEAD number" << endl;
		return nullptr;
	}

	// Since list is sorted, once we bit a larger integer we can stop
	while (current != nullptr && current->number <= number) {


		if(debug) {
			cout << "Comparing " << current->number 
				<< " to the search term, " << number << endl;
		}

		// This is the number, exit the loop
		if (current->number == number) {
			found = true;
			break;

		// Otherwise, keep traversing
		} else {
			++index;
			current = current->nextElement;	
		}
	}

	// Print out a message indicating whether or not it was found
	if (!internal) {
		cout << "Number " << number << " was " 
			<< (found ? "" : "not ") << "found." << endl;
		if (found) cout << "It is in position " << index << "." << endl;
	}

	return current;
}


/* ---------------------------- Internal Methods ------------------------*/

// Note: terribly inefficient! Insertion sort may work better, but
// this is a very simple implementation for now
void sortList(linkedList& list) {

	// First, sort the underlying array
	// Just a basic bubble sort 
	for (int i = 0; i < list.contents.size()-1; i++) {
		for (int j = 0; j < list.contents.size()-1; j++) {
			if (list.contents[j].number > list.contents[j+1].number) {
				entry temp = list.contents[j];
				list.contents[j] = list.contents[j+1];
				list.contents[j+1] = temp;
			}
		}
	}

	// Fix the 'head' pointer, and unlink the last node's 'next' pointer
	list.head = &list.contents.front();
	list.contents.back().nextElement = nullptr;

	// Now, go through and fix the rest of the 'next' pointers.
	for (int i =0; i < list.contents.size() - 1; i++) {
		list.contents[i].nextElement = &list.contents[i + 1];
	}

}
// Internal method, only for pretty-printing entries
void printEntry(const entry* entry, int index) {

	cout << "----------------------" << endl;
	cout << "Entry " << index << ":" << endl;
	cout << "Number: " << entry->number << endl;
	if (entry->nextElement != nullptr)
		cout << "Next: " << entry->nextElement->number << endl;
	cout << "----------------------" << endl;
}

void processMenuChoice(const MENU_CHOICE choice, linkedList& list) {
	
	switch(choice) {
		case ADD:
		{
			cout << "Enter number to be added:";
			int new_int = getValidatedInt(INT_MIN, INT_MAX);
			addNumber(list, new_int);
			cout << new_int << " added." << endl;
			break;
		}
		case DELETE:
		{
			cout << "Enter number to be deleted:";
			int del_int = getValidatedInt(INT_MIN, INT_MAX);
			bool deleted = deleteNumber(list, del_int);
			if (deleted) cout << del_int << " deleted." << endl;
			else cout << "Number not found in list." << endl;
			break;
		}
		case DISPLAY:
		{
			displayList(list);
			break;
		}
		case QUIT:
		{
			cout << "Thank you for using the best linked-list "
				<< "implementation of all time!" << endl;
			exit(0);
		}
		default:
		{
			cout << "Error: invalid menu choice received. Please try again." << endl;
			break;
		}
	}

}

void print_menu_options() {
	cout 
		<< "1: Add a Number To List" << endl
		<< "2: Delete a Number From List" << endl 
		<< "3: Display List" << endl
		<< "4: Exit Program" << endl
		<< "Enter menu choice: ";
}

MENU_CHOICE getMenuChoice() {

	int chances = menu_error_chances;
	print_menu_options();
	int choice = getValidatedInt(0, num_options);	

	while (!(1 <= choice && choice <= num_options)) {

		if (--chances < 0) {
			cout << "Input error. exiting program." << endl;
			exit(1);
		}

		cout << "Invalid choice, please enter again.";
		print_menu_options();
		cin.clear(); cin.ignore(INT_MAX,'\n'); 
		choice = getValidatedInt(0, num_options);
	}


	if(debug) cout << "getMenuChoice: Switching menu choice:"<<choice<<endl;

	switch (choice) {
		case 1: return ADD;
		case 2: return DELETE;
		case 3: return DISPLAY;
		case 4: return QUIT;
		default:
			cout << "Fatal error." << endl;
			exit(-1);
	}
}

/* Ensures input integer is in the range (min, max]. */
int getValidatedInt(const int min, const int max) {

	if(debug) cout << "Getting integer in range (" << min <<","<<max<<"]"<<endl;
	int chances = menu_error_chances;
	int temp;
	cin >> temp;

	while (!(temp > min && temp <= max)) {
		if (--chances < 0) { 
			cout << "Error: too many invalid inputs received. Exiting.." << endl;
			exit(1); 
		}
		cout << "Number out of range, please try again:" ;
		cin >> temp;
	}
	if(debug) cout << "Got int:"<<temp<<endl;
	
	// Clear input buffer so next input doesn't pick up extra chars
	cin.clear(); cin.ignore(INT_MAX,'\n');
	cout << endl;
	return temp;
}

void runTests() {
	linkedList* list = new linkedList;

	addNumber(*list, 5);
	assert (list->contents[0].number == 5); 

	addNumber(*list, 4);
	assert (list->contents[0].number == 4 && 
			list->contents[1].number == 5);

	addNumber(*list, 3);
	assert (list->contents[0].number == 3 && 
			list->contents[1].number == 4 &&
			list->contents[2].number == 5);

	addNumber(*list, 2);
	assert (list->contents[0].number == 2 && 
			list->contents[1].number == 3 &&
			list->contents[2].number == 4 &&
			list->contents[3].number == 5);

	addNumber(*list, 1);
	assert (list->contents[0].number == 1 && 
			list->contents[1].number == 2 &&
			list->contents[2].number == 3 &&
			list->contents[3].number == 4 &&
			list->contents[4].number == 5);

	if(debug) cout << "------- \"Add Number\" tests passed." << endl;

	if (debug) displayList(*list);

	assert (search(*list, 1) == true);
	assert (search(*list, 2) == true);
	assert (search(*list, 3) == true);
	assert (search(*list, 4) == true);
	assert (search(*list, 5) == true);

	assert (search(*list, INT_MIN) == false);
	assert (search(*list, INT_MAX) == false);

	cout << "------- \"Search\" tests passed." << endl;

	assert (deleteNumber(*list, 6) == false);
	assert (deleteNumber(*list, 0) == false);
	assert (deleteNumber(*list, INT_MIN) == false);
	assert (deleteNumber(*list, INT_MAX) == false);

	assert (deleteNumber(*list, 3) == true);
	assert (list->contents[0].number == 1 && 
			list->contents[1].number == 2 &&
			list->contents[2].number == 4 &&
			list->contents[3].number == 5);

	assert(deleteNumber(*list, 1) == true);
	assert (list->contents[0].number == 2 && 
			list->contents[1].number == 4 &&
			list->contents[2].number == 5);

	assert(deleteNumber(*list, 5) == true);
	assert (list->contents[0].number == 2 && 
			list->contents[1].number == 4); 

	assert(deleteNumber(*list, 2) == true);
	assert (list->contents[0].number == 4); 

	assert(deleteNumber(*list, 2) == false);

	assert(deleteNumber(*list, 4) == true);
	assert(list->contents.size() == 0); 

	if (debug) cout << "------- \"deleteNumber\" tests passed." << endl;

	delete list;
}

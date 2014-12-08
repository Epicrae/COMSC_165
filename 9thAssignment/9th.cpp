#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

#define DATA_FILE "records.dat"

struct Record {
	string name;
	int quantity;
	double wholesale;
	double retail;
};

void change_record(Record*);
void printRecord(const Record&);
vector<Record> getRecordsFromFile();
vector<struct Record> makeNewRecords();
void write_to_file(const vector<Record>&, fstream &outfile);
Record* findRecordByName(const string&, vector<Record>&);
struct Record createRecord(string name, int quantity, double wholesale, double retail);

int getMenuChoice();
void print_menu_options();
void processMenuChoice(const int);

char* encrypt(const char plain_text[]);
char* decrypt(const char cipher_text[]);

char* getScrubbedString();
double getValidatedDouble();
int getValidatedInt(const int, const int);

void run_tests();
bool debug_on = false;

/* Calls the main menu, and loops until exit is selected, or a certain 
 * number of incorrect menu choices have been made. */
int main() {
	if (debug_on) { run_tests(); }

	int choice;
	do {
		choice = getMenuChoice();
		processMenuChoice(choice);
	} while (choice != 6);
	return 0;
}

/* Run basic tests, set 'debug_on' to true in header. */
void run_tests() {
	cout << "hw" << endl;
	Record r = createRecord("Default", 5, 2.2, 1.1);
	cout << r.name;
}

/* Maps the choices from the main menu to the appropriate functions. */
void processMenuChoice(const int choice) {

	switch (choice) {

		case 1: // Add records to file
		{ 			// Braces needed for block scoping

			cout << "Mode: Adding new records." << endl;
			fstream outfile;
			
			// Check if file exists first.
			outfile.open(DATA_FILE, ios::app);

			if (outfile.fail()) {
				cout << "Output file not found. Creating a new one..." << endl;
				outfile.open(DATA_FILE, ios::out);
			} else { 
				cout << "Output file found. Appending.." << endl;
			}
			
			vector<struct Record> records = makeNewRecords();
			
			write_to_file(records, outfile);
			
			break;
		}
		case 2: // Display record from file
		{
			vector <Record> records = getRecordsFromFile();

			cout << "Enter search term: ";
			string search_term = getScrubbedString();

			Record* r = findRecordByName(search_term, records);

			if (r == nullptr) {
				cout << "Record not found." << endl;
				break;
			}

			cout << "Record found. Details:" << endl;
			printRecord(*r);
			break;
		}
		case 3: // Change record from file	
		{
			cout << "Enter search term: ";
			string search_term = getScrubbedString();;

			vector <Record> records = getRecordsFromFile();
			Record* to_change = findRecordByName(search_term, records);
			if (to_change == nullptr) {
				cout << "Record not found." << endl;
				break;
			}

			change_record(to_change);

			cout << "Writing record back to file.." << endl;
			fstream outfile(DATA_FILE, ios::out);
			write_to_file(records, outfile);
			cout << "File written successfully." << endl;

			break;
		}
		case 4: // Display all records
		{
			cout << "Mode: Reading/Displaying all records." << endl;
			
			vector <Record> records = getRecordsFromFile();

			for (int i = 0; i < records.size(); i++) {
				cout << "------ Record " << i << " ------" << endl;
				printRecord(records[i]);
			}
			break;
		}
		case 5: // Prepare report
		{
			vector<Record> records = getRecordsFromFile();
			int quantity_tot = 0;
			double wholesale_tot = 0.0;
			double retail_tot = 0.0;
			for (auto &r : records) {
				printRecord(r);
				quantity_tot += r.quantity;
				wholesale_tot += r.wholesale;
				retail_tot += r.retail;
			}
			cout << "----- Report -----" << endl
				<< "Total Quantity: " << quantity_tot << endl
				<< "Total Retail Value: " << retail_tot << endl
				<< "Total Wholesale Value: " << wholesale_tot << endl
				<< "-------------------------------" << endl;
			break;
		}
		case 6: // Exit
			break;	
		default:
			// Shouldn't happen, due to input scrubbing.
			cout << "Unknown error, exiting program." << endl;
			exit(1);
	}
}

/* Given a record to change, prints a menu allowing the user to select which 
 * file should be updated, and writes the changes back into the record. */
void change_record(Record* to_change) {

	int change_choice;
	cout << "Which field would you like to change?" << endl 
		<< "(1): Name" << endl
		<< "(2): Quantity" << endl
		<< "(3): Wholesale Value" << endl
		<< "(4): Retail Value" << endl
		<< "(5): Return to Main Menu" << endl;
	change_choice = getValidatedInt(0,5);
	cout << "Selected choice " << change_choice << endl;

	cout << "Old Record Details:" << endl;
	printRecord(*to_change);

	switch(change_choice) {

		case 1: 
		{
			cout << "Enter new name: ";
			char* n = getScrubbedString();
			string name = n;
			to_change->name = name;
			break;
		}
		case 2:
		{
			cout << "Enter new quantity: ";
			int q;
			cin >> q;
			to_change->quantity = q;
			break;
		}
		case 3:
		{
			cout << "Enter new wholesale value: ";
			double w;
			cin >> w;
			to_change->wholesale = w;
			break;
		}
		case 4:
		{
			cout << "Enter new retail value: ";
			double v;
			cin >> v;
			to_change->retail = v;
			break;
		}
		case 5:
			cout << "Exiting.." << endl;
			break;
		default:
			cout << "Fatal error." << endl;
			exit(-1);
	}

	cout << "New Record Details:" << endl;
	printRecord(*to_change);
}

/* Common to several choices. Open a file for writing or appending first. */
void write_to_file(const vector<Record>& records, fstream &outfile) {

	for (auto &r : records) {
		outfile 
			<< r.name << endl
			<< r.quantity << endl 
			<< r.wholesale << endl
			<< r.retail << endl;
	}
	outfile.close();	
}

Record* findRecordByName(const string& search_name, vector<Record>& records) {

	Record* returnRecord = nullptr;
	bool found = false;

	for (auto &r : records) {
		if (r.name.compare(search_name) == 0) {
			found = true;
			returnRecord = &r;
		}
	}

	if (!found) cout << "Record not found." << endl;
	return returnRecord;
}

void printRecord(const Record& r) {

	cout << "-------------------" << endl;
	cout 
		<< "Name: " << r.name << endl
		<< "Quantity: " << r.quantity << endl 
		<< "Wholesale Price: " << r.wholesale << endl 
		<< "Retail Price: " << r.retail << endl; 
	cout << "-------------------" << endl;
}

vector <Record> getRecordsFromFile() {

	vector<struct Record> records;
	
	fstream infile;
	infile.open(DATA_FILE, ios::in);

	if (!infile) {
		cout << "Error opening data file." << endl;
	} else {
		cout << "Record file found." << endl;
		string in_line;
		cout << "Reading records..." << endl;

		string name;
		int quant;
		double whole, retail;

		while( infile >> name ) {
			infile >> quant;
			infile >> whole;
			infile >> retail;
			records.push_back(
					createRecord(name, quant, whole, retail)
				);
		}
		infile.close();
	}
	return records;
}

struct Record createRecord(string name, int quantity, 
		double wholesale, double retail) {

	struct Record r;
	r.name = name; 
	r.quantity = quantity;
	r.wholesale = wholesale;
	r.retail = retail;

	return r;
}

vector<struct Record> makeNewRecords() {

	vector<struct Record> records;
	char* cont = new char[1];
	cout << "----- Add records ----------" << endl;

	do {
		cout << "Enter name: ";
		char* name = getScrubbedString();
		cout << "Enter quantity: ";
		int quantity = getValidatedInt(0, INT_MAX);
		cout << "Enter wholesale price: ";
		double wholesale = getValidatedDouble();
		cout << "Enter retail price: ";
		double retail = getValidatedDouble();
		records.push_back(createRecord(name, quantity, wholesale, retail));
		cout << "Add another record? (y/n) ";
		*cont = getchar();
		cin.clear(); cin.ignore(INT_MAX,'\n'); 
	} while (*cont == 'y');

	return records;
}

/* Ensures a valid menu choice is entered. 
 * #ToDo - replaced with getValidatedInt(0, 6). */
int getMenuChoice() {

	int chances = 5;
	print_menu_options();
	int choice = getValidatedInt(0, 6);	

	while (!(1 <= choice && choice <= 6)) {
		if (--chances < 0) {
			cout << "Input error. exiting program." << endl;
			exit(1);
		}
		cout << "Invalid choice, please enter again.";
		print_menu_options();
		cin.clear(); cin.ignore(INT_MAX,'\n'); 
		choice = getValidatedInt(0, 6);
	}

	return choice;
}

void print_menu_options() {

	cout 
		<< "1: Add Records to File" << endl
		<< "2: Display a Record From File" << endl
		<< "3: Change a Record From File" << endl 
		<< "4: Display All Records" << endl
		<< "5: Prepare Report" << endl
		<< "6: Exit Program" << endl
		<< "Enter menu choice: ";
}

/* Ensures input integer is in the range (min, max]. */
int getValidatedInt(const int min, const int max) {

	int chances = 5;
	int temp;
	cin >> temp;

	while (!(temp > min && temp <= max)) {
		if (++chances > 5) { exit(1); }
		cout << "Number must be positive." << endl;
		cin >> temp;
	}
	
	// Clear input buffer so next input doesn't pick up extra chars
	cin.clear(); cin.ignore(INT_MAX,'\n'); 
	return temp;
}

/* Ensures input double is greater than zero. */
double getValidatedDouble() {

	// Only allow 5 incorrect selections
	// (Prevents infinite loops)
	int chances = 5;
	double temp;
	cin >> temp;

	while (!(temp > 0)) {
		if (++chances > 5) { exit(1); }
		cout << "Number must be positive." << endl;
		cin >> temp;
	}

	cin.clear(); cin.ignore(INT_MAX,'\n'); 
	return temp;
}

/* Gets input and removes trailing newline */
char* getScrubbedString() {

	char* temp = new char[50];
	fgets(temp, 50, stdin);

	for (int i = 0; i < 50; i++) {
		if (temp[i] == '\n') { temp[i] = '\0'; } 
	}

	return temp;
}

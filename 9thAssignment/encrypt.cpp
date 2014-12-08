#include<iostream>
#include<string>
#include<fstream>
#include<cmath>

using namespace std;

#define ENC_FILE "encrypted.dat"
#define UNENC_FILE "unencrypted.dat"

string encrypt(string);
string decrypt(string);

void writeToFile(string);
string readOriginalFile();
string readFromEncryptedFile();

// Returns true if the messages are equal.
bool compareMessages(string, string);

// Pretty-prints the message
void printMessage(string);

/* Reads a message from a file, encrypts it, and displays the contents.
 * Then, writes the encrypted message to a file.
 * Then, reads the encrypted message from the file, decrypts it, and
 * compares it to the original message. Prints out whether or not they match. 
 */
int main(void) {

	string original_message = readOriginalFile();

	cout << "Original Message" << endl;
	printMessage(original_message);

	string encrypted_msg = encrypt(original_message);

	cout << "Encrypted Message" << endl;
	printMessage(encrypted_msg);

	writeToFile(encrypted_msg);

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	string encrypted_file_msg = readFromEncryptedFile();
	cout << "Encrypted Message from File" << endl;
	printMessage(encrypted_file_msg);

	string unencrypted_file_msg = decrypt(encrypted_file_msg);
	cout << "Decrypted Message from File" << endl;
	printMessage(unencrypted_file_msg);

	cout << endl;
	if ( compareMessages(original_message, unencrypted_file_msg) ) {
		cout << "Decryption successful, messages match." << endl;
	} else {
		cout << "Decryption failed. Messages do not match." << endl;
	}

	return 0;
}

bool compareMessages(string a, string b) {
	return a.compare(b) == 0 ? true : false;
}

string encrypt(string msg) {

	string output(msg);

	for (int i = 0; i < msg.size(); i++) {
		output[i] = msg[i] + 10;
	}
	return output;
}

string decrypt(string msg) {

	string output(msg);

	for (int i = 0; i < msg.size(); i++) {
		output[i] = msg[i] - 10; 
	}
	return output;
}

string readFromEncryptedFile() {

	ifstream infile(ENC_FILE);

	string message ( (istreambuf_iterator<char>(infile)) ,
			(istreambuf_iterator<char>()) );
	return message;
}

void writeToFile(string enc_msg) {

	ofstream outfile(ENC_FILE);
	
	if (outfile.is_open()) {
		outfile << enc_msg;
	} else {
		cout << "Error opening file." << endl;
	}
}

string readOriginalFile() {

	ifstream infile(UNENC_FILE);
	string message ( (istreambuf_iterator<char>(infile)) ,
			(istreambuf_iterator<char>()) );
	return message;
}

void printMessage(string msg) {

	cout << "--------------------------" << endl 
		<< msg 
		<< "\n--------------------------" << endl;
}

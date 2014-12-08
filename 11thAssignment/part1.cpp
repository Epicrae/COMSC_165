#include<iostream>
#include<string>
#include <assert.h>

using namespace std;

bool is_palindrome(string);

int main(void) {

	cout << "Starting tests..." << endl;

	const int num_tests = 5;

	string strings[num_tests] = { 
		"aibohphobia", "detartrated", "aba", "abba", "wassamassaw" 
	};

	string not_strings[num_tests] = {
		"ab", "abc", "abcbba", "abcdedbcc", "ccccdecccc"
	};

	for (int i = 0; i < num_tests; i++) {

		assert (is_palindrome(strings[i]));
		assert(!is_palindrome(not_strings[i]));

		cout << strings[i] << (is_palindrome(strings[i]) 
				? " is a palindrome"  
				: " is not a palindrome" ) 
			<< endl;

		cout << not_strings[i] << (is_palindrome(not_strings[i]) 
				? " is a palindrome"  
				: " is not a palindrome" ) 
			<< endl;
	}
	cout << "All tests passed." << endl;

	string user_input;
	cout << "Enter string to recursively check for palindrome-ness" << endl;
	cin >> user_input;

	cout << (is_palindrome(user_input) 
			? "Word is a palindrome"  
			: "Word is not a palindrome" ) 
		<< endl;

	return 0;
}

bool is_palindrome(string s) {

	if (s.size() <= 1) 
		return true;
	if (s.front() != s.back()) {
		return false;
	} else {
		return true && is_palindrome(s.substr(1, s.size() - 2));
	}
}

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

int main(void) {


	string input;
	cout << "Enter English string: ";
	getline(std::cin, input, '\n');
	stringstream s(input);

	cout << "Input was: " << input << endl;
	vector<string> tokens;
	string buffer;

	while (getline(s, buffer, ' ')) {
		tokens.push_back(buffer);
	}

	string result;
	for (string &t : tokens) {
		if(t.size() == 1) {
			result += t + " ";
		} else {
			result += t.substr(1, t.size()) + t[0] + "AY ";
		}
	}
	cout << "Result: " << result << endl;

	return 0;
}

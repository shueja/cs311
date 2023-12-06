#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char* argv[]) {
	// If we don't have at least 1 argument for the name (argc is always at least 1 because of the filename)
	if (argc < 2) {
		cout << "This program needs a command line argument!" << endl;
	} else {
		// Use the second argument of argv (the name passed in)
		cout << "Hello, " << argv[1] << "! Welcome to CS 311" << endl;
	}
}

#include <iostream>

using namespace std;

void panic(string msg) {
	cerr << msg << endl;
	exit(1);
}

void invalidSyntax(string str, int index, int len = 1) {
	panic(
		"Unexpected syntax:\n"
		+ str + "\n"
		+ string(index, ' ') + "\033[31m" + string(len, '^') + "\033[0m"
	);
}

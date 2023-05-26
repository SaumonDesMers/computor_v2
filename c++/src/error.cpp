#include <iostream>

using namespace std;

void panic(string msg) {
	cerr << msg << endl;
	exit(1);
}
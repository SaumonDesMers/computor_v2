#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

using namespace std;

void panic(string msg);
void invalidSyntax(string str, int index, int len = 1);

#endif
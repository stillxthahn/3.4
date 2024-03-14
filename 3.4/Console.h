#ifndef CONSOLE_H
#define CONSOLE_H
#include <Windows.h>
#include "Entry.h"
class Console {
public:
	static void GoToXY(int x, int y);
	static void Display(const vector<Entry*>& entries);
private:
	static int RecursivePrint(Entry* e, int x, int y);
};
#endif

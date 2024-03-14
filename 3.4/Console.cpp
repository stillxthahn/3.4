#pragma once
#include "Console.h"
#include <string>
using namespace std;

void Console::GoToXY(int x, int y) {
	COORD coords;
	coords.X = x;
	coords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}
void Console::Display(const vector<Entry*>& entries) {
	int x = 0;
	int y = 0;
	int tab = 25;
	system("cls");
	for (int i = 0; i < entries.size(); ++i) {
		GoToXY(x, y);
		Entry* e = entries[i];
		bool hasParent = false;
		// Check whether Entry has parent or not. If it has, then ignore it because it was already visited
		for (int j = i; j >= 0; --j) {
			if (e->IsParent(entries[j])) {
				hasParent = true;
				break;
			}
		}
		if (hasParent)
			continue;
		string name = e->GetFileName();
		cout << name;
		if (e->IsFolder()) {
			if (e->SubEntryList().size() != 0) {
				cout << '|';
				GoToXY(x + name.length(), y + 1);
				for (int i = 0; i < tab - name.length(); ++i)
					cout << '-';
			}
			y = RecursivePrint(e, x + tab, y + 1);
		}
		++y;
	}
	cout << '\n';
}
int Console::RecursivePrint(Entry* e, int x, int y) {
	int tab = 25;
	vector<Entry*> subEntryList = e->SubEntryList();
	if (subEntryList.size() == 0)
		return y - 1;
	for (int i = 0; i < subEntryList.size(); ++i) {
		GoToXY(x, y);
		string name = subEntryList[i]->GetFileName();
		cout << name;
		if (subEntryList[i]->IsFolder()) {
			if (subEntryList[i]->SubEntryList().size() != 0) {
				cout << '|';
				GoToXY(x + name.length(), y + 1);
				for (int i = 0; i < tab - name.length(); ++i)
					cout << '-';
			}
			y = RecursivePrint(subEntryList[i], x + tab, y + 1);
		}
		++y;
	}
	return y;
}
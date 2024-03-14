#include "MenuUI.h"
#include "Entry.h"
#include <vector>
#include "VolumeAPI.h"
#include <iostream>
#include "VolumeInfo.h"
#include <string>
#include "Console.h"

using namespace std;
void MenuUI::createMenu(FILE* fp, VolumeInfo* v, vector<char>& fatTable) {
	int work = -1;
	while (work != 0)
	{
		system("cls");
		cout << R"(
	.===========================================================.
	||      1. List all directories and files in volume.       ||
	||      2. Import 1 file/folder into volume.               ||
	||      3. Delete 1 file from volume.                      ||
	||      4. Export 1 file/folder from volume.               ||
	||      5. Change volume's password.                       ||
	||      0. Back to main Menu.                              ||
	*===========================================================*
	> Your choice: )";
		cin >> work;
		cin.ignore();
		string sourcePath = "";
		string sourceName = "";
		string targetName = "";
		string password = "";
		vector<Entry*> entries;
		string nameForDel = "";
		string pw;
		SHA256 pw256;
		switch (work)
		{
		case 1:
			entries = VolumeAPI::listEntry(fp, v, fatTable);
			Console::Display(entries);
			VolumeAPI::ListEntryFreeMemory(entries);
			system("pause");
			break;
		case 2:
			cout << "	Input imported file's path: ";
			getline(cin, sourcePath);
			cout << "	Input file name: ";
			getline(cin, targetName);
			cout << "	Enter password: ";
			cin >> password;
			cout << endl;
			if (VolumeAPI::saveFileToData(fp, v, fatTable, sourcePath, targetName, password)) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (2 * 16));
				cout << "	IMPORT FILE SUCCESSFUL!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (4 * 16));
				cout << "	NOT ENOUGH SAPCE!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			system("pause");
			break;
		case 3:
			cout << "	Input file name to delete: ";
			cin >> nameForDel;
			cout << endl;
			if (entries.size() == 0)
				entries = VolumeAPI::listEntry(fp, v, fatTable);
			if (VolumeAPI::deleteFile(fp, v, fatTable, nameForDel, entries)) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (2 * 16));
				cout << "	DELETE FILE SUCCESSFUL!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (4 * 16));
				cout << "	FILE DOESN'T EXIST OR WRONG PASSWORD" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			system("pause");
			break;
		case 4:
			if (entries.size() == 0)
				entries = VolumeAPI::listEntry(fp, v, fatTable);
			for (int i = 0; i < entries.size(); i++) {
				cout << "	Name: ";
				cout << entries[i]->Name() << endl;
				cout << "	Path: ";
				cout << entries[i]->Path() << endl;
				cout << '\n';
			}
			cout << "	Input file/folder to export: ";
			getline(cin, sourceName);
			cout << "	Input destination path: ";
			getline(cin, targetName);
			cout << endl;
			if (VolumeAPI::exportFile(fp, v, fatTable, entries, sourceName, targetName)) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (2 * 16));
				cout << "	EXPORT SUCCESSFUL!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (4 * 16));
				cout << "	FILE DOESN'T EXIST OR WRONG PASSWORD" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			system("pause");
			break;
		case 5:
			cout << "	Input old password: "; getline(cin, pw);
			cout << endl;
			//mat khau dung
			if (v->checkPassword(pw)) {
				cout << "	Input new password: "; getline(cin, pw);
				v->SetVolPass(pw);
				fseek(fp, 0, SEEK_SET);
				v->writeVolInfo(fp);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (2 * 16));
				cout << "	CHANGE PASSWORD SUCCESSFUL!.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (4 * 16));
				cout << "	WRONG PASSWORD" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		case 0:
			return;
		default:
			cout << "	INVALID CHOICE!" << endl;
			break;
		}
	}
}
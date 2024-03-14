//tam thoi dung quan tam toi entry table.
#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include"VolumeInfo.h"
#include"Entry.h"
#include<string>
#include<vector>
#include <stack>
#include"VolumeAPI.h"
#include "MenuUI.h"
#include <direct.h>
using namespace std;

int main()
{
	FILE* fp = nullptr;
	string name = "";
	int work = -1;
	errno_t err;
	VolumeInfo* v;
	int size = 0;
	vector<char> fatTable;
	while (work != 0)
	{
		system("cls");
		cout << R"(
	.======================================.
	||      1 -- Create new volume.       ||
	||      2 -- Open existing volume.    ||
	||      0 -- Exit program.            ||
	*====================================*
	> Your choice:  )";
		cin >> work;
		cin.ignore();
		switch (work)
		{
		case 1:
			cout << "	Input put volume's name or path: ";
			getline(cin, name);
			cout << "	Input volume's size (>0; MB): ";
			cin >> size;

			// ------------- Create volume ---------------
			VolumeAPI::initVolume(name, size * 1024 * 1024);
			// ------------- Create volume ---------------

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + (2 * 16));
			cout << "	CREATE VOLUME SUCCESSFUL!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			system("pause");
			break;
		case 2:
			cout << "	Input existing volume: ";
			getline(cin, name);
			err = fopen_s(&fp, name.c_str(), "rb+");
			if (err == 0) {
				v = VolumeAPI::readVolumeInfo(fp);
				// Check Signature
				if (v->Signature() != 0x00444448) {
					cout << "\n	This program can not open this volume!";
					break;
				}

				// Check password
				string pw;
				cout << "	Input password: "; getline(cin, pw);

				// If password is correct
				if (v->checkPassword(pw)) {
					// Read FAT Table
					fatTable = VolumeAPI::readFatTable(fp, v);
					MenuUI::createMenu(fp, v, fatTable);
					fclose(fp);
				}
				else {
					cout << "	Wrong password!\n";
					fclose(fp);
				}
				delete v;
			}
			else {
				cout << "	Volume doesn't exist!" << endl;
			}
			system("pause");
			break;
		case 0:
			if (fp)
				fclose(fp);
			work = 0;
			break;
		default:
			cout << "	Invalid choice!" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

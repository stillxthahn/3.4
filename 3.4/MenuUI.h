#include <iostream>
#include <stdio.h>
#include"VolumeInfo.h"
#include"Entry.h"
#include<string>
#include<vector>
class MenuUI {
public:
	static void createMenu(FILE* fp, VolumeInfo* v, vector<char>& fatTable);
};
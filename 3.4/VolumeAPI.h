#ifndef VOLUME_API_H
#define VOLUME_API_H
//tam thoi dung quan tam toi entry table.
#include <iostream>
#include <stdio.h>
#include"VolumeInfo.h"
#include"Entry.h"
#include<string>
#include<vector>
#define  VOLUME_SIZE_DEFAULT 8000000
#define CLUSTER_SIZE 2048
const int BUFFER_SIZE = 512;
class VolumeAPI {
public:
	//Khoi tao 1 vung volume trong
	static void initVolume(string name, int volumeSize = VOLUME_SIZE_DEFAULT);
	//doc thong tin volumeInfo
	static VolumeInfo* readVolumeInfo(FILE* fp);
	//doc thong tin bang fat
	static vector<char> readFatTable(FILE* fp, VolumeInfo* v);
	//doc thong tin cac Entry
	static vector<Entry*> listEntry(FILE* f, VolumeInfo* v, vector<char> fatTable);
	//giai phong memory cho cac entry duoc cap phat truoc do
	static void ListEntryFreeMemory(vector<Entry*>& entries);
	//Tim cluster trong
	static int FindEmptyCluster(vector<char>& fatTable, int dataSize);
	//chep file
	static bool saveFileToData(FILE*& fp, VolumeInfo*& v, vector<char>& fatTable, string sourceName, string targetName, string password);
	static bool deleteFile(FILE* fp, VolumeInfo* v, vector<char>& fatTable, string name, vector<Entry*> listEntry);
	static bool exportFile(FILE* fp, VolumeInfo* v, const vector<char>& fatTable, const vector<Entry*>& listEntry, string sourceName, string targetName);
};
#endif
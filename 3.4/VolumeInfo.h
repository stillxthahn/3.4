#pragma once
#ifndef VOLUMEINFO_H
#define VOLUMEINFO_H

#include <iostream>
#include <fstream>
#include "Sha256.h"
using namespace std;
class VolumeInfo
{
private:
	//static uint32_t const _DefaultSignature;
	/*==========*/
	uint32_t _Signature;
	uint32_t _SizeEntryTable;
	uint32_t _NumberOfEntry;
	uint64_t _OffsetEntryTable;
	uint64_t _VolumeSize;
	uint16_t volPassSize;
	string volPass;
public:
	VolumeInfo() {};
	VolumeInfo(uint32_t volumeSize);
	//~VolumeInfo();
	uint32_t Signature() { return _Signature; }
	uint32_t SizeEntryTable() { return _SizeEntryTable; }
	void SetSizeEntryTable(uint32_t value) { _SizeEntryTable = value; }
	uint32_t NumberOfEntry() { return _NumberOfEntry; }
	void SetNumberOfEntry(uint32_t value) { _NumberOfEntry = value; }
	uint64_t VolumeSize() { return _VolumeSize; }
	void SetNVolumeSize(uint32_t value) { _VolumeSize = value; }
	void SetVolPass(string pw) { volPass = pw; volPassSize = volPass.size(); }
	uint16_t volPassLen() { return volPassSize; }
	uint16_t volumeInfoSize() { return 30 + volPassSize; }
	/*==========*/
	bool checkPassword(string pw);
	void writeVolInfo(FILE* f);
	void readVolInfo(FILE* f);
	//Update SizeEntryTable and NumberOfEntry
	void UpdateVol(FILE* f);
};
#endif
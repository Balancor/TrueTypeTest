//
// Created by guoguo on 17-3-21.
//

#ifndef GTRUETYPE_UTILS_H
#define GTRUETYPE_UTILS_H

#include <iostream>
#include "Base.h"
#include "CmapTable.h"

short readTwoBytesAsShort(const char* const  content);
unsigned short readTwoBytesAsUShort(const char* const  content);
int readFourBytesAsInt(const char* const  content);
unsigned int readFourBytesAsUInt(const char* const  content);

uint32_t calcTableChecksum(uint32_t *Table, uint32_t Length);

char* readFromFontFile(const char* fileName);
char* readNumberBytesFromFile(const char* fileName, unsigned int offset, unsigned int count);
DirectoryTable* getDirectoryTable(const char* fileName);
CmapTable* getCmapTable(const char* fileName);

#endif //GTRUETYPE_UTILS_H

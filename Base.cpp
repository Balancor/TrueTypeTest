// Created by guoguo on 17-3-23.
#include "Base.h"
#include "utils.h"
DirectoryTable::DirectoryTable(const char* fontFileName){
    const char* const content = readFromFontFile(fontFileName);
    int offset = 0;
    this->sfntVersion = readFourBytesAsUInt(content + offset);
    offset += 4;
    this->mNumTables = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mSearchRange = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mEntrySelector = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mRangeShift = readTwoBytesAsUShort(content + offset);
    offset += 2;

    mTableRecords = (TableRecord**)malloc(sizeof(void*) * mNumTables);
    for (int i = 0; i < mNumTables; ++i) {
        TableRecord *record =  (TableRecord*)malloc(sizeof(TableRecord));
        record->tag = readFourBytesAsUInt(content + offset);
        offset += 4;
        record->checkSum = readFourBytesAsUInt(content + offset);
        offset += 4;
        record->offset = readFourBytesAsUInt(content + offset);
        offset += 4;
        record->length = readFourBytesAsUInt(content + offset);
        offset += 4;
/*
        printf("Tag: %c%c%c%c, offset: %u\n",
               record->tag >> 24 & 0xFF,record->tag >> 16 & 0xFF,
               record->tag >> 8 & 0xFF,record->tag & 0xFF,
               record->offset);
*/
        this->mTableRecords[i] = record;
    }
}

TableRecord* DirectoryTable::getTableRecord(uint32_t tag){
    if(mTableRecords){
        for (int i = 0; i < mNumTables; ++i) {
            TableRecord *record = mTableRecords[i];
            if(!(tag - record->tag)){
                return record;
            }
        }
    }
    return NULL;
}
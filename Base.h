//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_BASE_H
#define GTRUETYPE_BASE_H

#include <iostream>

typedef struct {
    uint32_t tag;
    uint32_t checkSum;
    uint32_t offset;
    uint32_t length;
}TableRecord;


class DirectoryTable {
protected:
    uint32_t 	sfntVersion;
    uint16_t 	mNumTables;
    uint16_t 	mSearchRange;
    uint16_t 	mEntrySelector;
    uint16_t 	mRangeShift;
    TableRecord** mTableRecords;
public:
    DirectoryTable(const char* fontFileName);
    TableRecord* getTableRecord(uint32_t tag);
    ~DirectoryTable(){
        if(mTableRecords != NULL){
            for (int i = 0; i < mNumTables; ++i) {
                TableRecord* record = mTableRecords[i];
                free(record);
            }
            free(mTableRecords);
        }
    }
};


class Table{
protected:
    uint32_t mOffset;
    uint32_t mLength;
    char* mRawData;

public:
    ~Table(){
        if(mRawData != NULL)
            free((void*)mRawData);
    }

    virtual void setOffset(uint32_t offset) = 0;
};

#endif //GTRUETYPE_BASE_H

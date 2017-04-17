//
// Created by guoguo on 17-3-22.
//
#include <cstring>
#include "GTrueType_defs.h"
#include "CmapTable.h"
#include "../utils.h"
#include "Base.h"

CmapTable::CmapTable(const char* fileName){
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* cmapRecord = directoryTable->getTableRecord(TABLE_TAG_CMAP);
    if(cmapRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }

    this->mOffset = cmapRecord->offset;
    this->mLength = 0;
    char* content = readNumberBytesFromFile(fileName, mOffset, 4);

    mVersion = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mNumTable = readTwoBytesAsUShort(content + mLength);
    mLength += 2;

    char* encodingRecordContent = readNumberBytesFromFile(fileName, mOffset + mLength,
                                                          ENCODING_TABLE_LENGTH * mNumTable);

    mEncodingTableRecords = (EncodingTableRecord**)malloc(sizeof(void*) * mNumTable);
    int offset = 0;
    for (int i = 0; i < mNumTable; ++i) {
        EncodingTableRecord* record = (EncodingTableRecord*)
                malloc(sizeof(EncodingTableRecord));
        record->platformID = readTwoBytesAsUShort(encodingRecordContent + offset);
        offset += 2;
        record->encodingID = readTwoBytesAsUShort(encodingRecordContent + offset);
        offset += 2;
        record->offset = readFourBytesAsUInt(encodingRecordContent + offset);
        offset += 4;
        mEncodingTableRecords[i] = record;
    }

    this->mLength = mLength + offset;

    this->mRawData = (char*)malloc(sizeof(char) * (mLength + 1));
    for (int j = 0; j < mLength; ++j) {
        mRawData[j] = content[j];
    }
    mRawData[mLength] = '\0';
    free(content);
    free(encodingRecordContent);
    content = NULL;
    encodingRecordContent = NULL;
}

EncodingTableRecord* CmapTable::getEncodingRecord(uint16_t platformId, uint16_t encodingId){
    if(mEncodingTableRecords){
        for (int i = 0; i < mNumTable; ++i) {
            EncodingTableRecord* record = mEncodingTableRecords[i];
            if(platformId == record->platformID &&
               encodingId == record->encodingID){
                return record;
            }
        }
    }
    return NULL;
}
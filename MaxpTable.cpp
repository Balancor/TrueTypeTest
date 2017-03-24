//
// Created by guoguo on 17-3-23.
//
#include "GTrueType_defs.h"
#include "MaxpTable.h"
#include "utils.h"
MaxpTable::MaxpTable(const char* fileName){
    printf("CmapTable Constructor, fileName: %s\n", fileName);

    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* maxpRecord = directoryTable->getTableRecord(TABLE_TAG_MAXP);
    if(maxpRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }
    this->mOffset = maxpRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, MAXP_TABLE_LENGTH);

    mMaxpTableVersion = readFourBytesAsUInt(content + mOffset + mLength);
    mLength += 2;
    mNumGlyphs = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxPoints = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxContours = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxCompositePoints = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxCompositeContours = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxZones = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxTwilightPoints = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxStorage = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxFunctionDefs = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxInstructionDefs = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxStackElements = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxSizeOfInstructions = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxComponentElements = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;
    mMaxComponentDepth = readTwoBytesAsUShort(content + mOffset + mLength);
    mLength += 2;

    free(content);
    content = NULL;
}
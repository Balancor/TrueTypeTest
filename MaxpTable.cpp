//
// Created by guoguo on 17-3-23.
//
#include "GTrueType_defs.h"
#include "MaxpTable.h"
#include "utils.h"
MaxpTable::MaxpTable(const char* fileName){
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* maxpRecord = directoryTable->getTableRecord(TABLE_TAG_MAXP);
    if(maxpRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }
    this->mOffset = maxpRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, MAXP_TABLE_LENGTH);

    mMaxpTableVersion = readFourBytesAsUInt(content + mLength);
    mLength += 4;
    mNumGlyphs = readTwoBytesAsUShort(content + mLength);
    mLength += 2;

    if(mMaxpTableVersion == 0x5000){
        free(content);
        content = NULL;
        return;
    }

    mMaxPoints = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxContours = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxCompositePoints = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxCompositeContours = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxZones = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxTwilightPoints = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxStorage = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxFunctionDefs = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxInstructionDefs = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxStackElements = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxSizeOfInstructions = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxComponentElements = readTwoBytesAsUShort(content + mLength);
    mLength += 2;
    mMaxComponentDepth = readTwoBytesAsUShort(content + mLength);
    mLength += 2;

    free(content);
    content = NULL;
}

void MaxpTable::dump(){
    printf("MaxpTable:\n");
    printf("\tmMaxpTableVersion: %u\n", mMaxpTableVersion);
    printf("\tmNumGlyphs: %u\n", mNumGlyphs);
    if(mMaxpTableVersion == 0x5000)
        return;
    printf("\tmMaxPoints: %u\n", mMaxPoints);
    printf("\tmMaxContours: %u\n", mMaxContours);
    printf("\tmMaxCompositePoints: %u\n", mMaxCompositePoints);
    printf("\tmMaxCompositeContours: %u\n", mMaxCompositeContours);
    printf("\tmMaxZones: %u\n", mMaxZones);
    printf("\tmMaxTwilightPoints: %u\n", mMaxTwilightPoints);
    printf("\tmMaxStorage: %u\n", mMaxStorage);
    printf("\tmMaxFunctionDefs: %u\n", mMaxFunctionDefs);
    printf("\tmMaxInstructionDefs: %u\n", mMaxInstructionDefs);
    printf("\tmMaxStackElements: %u\n", mMaxStackElements);
    printf("\tmMaxSizeOfInstructions: %u\n", mMaxSizeOfInstructions);
    printf("\tmMaxComponentElements: %u\n", mMaxComponentElements);
    printf("\tmMaxComponentDepth: %u\n", mMaxComponentDepth);
}
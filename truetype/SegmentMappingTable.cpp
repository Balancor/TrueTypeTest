//
// Created by guoguo on 17-3-22.
//

#include <cstring>
#include "SegmentMappingTable.h"
#include "../utils.h"
#include "GTrueType_defs.h"

SegmentMappingTable::SegmentMappingTable(const char* fileName, uint16_t platformId, uint16_t encodingId){
    CmapTable* cmapTable = getCmapTable(fileName);
    EncodingTableRecord* tableRecord = cmapTable->getEncodingRecord(platformId, encodingId);
    if(tableRecord == NULL){
        printf("Cannot get Encoding Table Record\n");
        return ;
    }

    this->mOffset = cmapTable->mOffset + tableRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, SEGMENT_SUBTABLE_HEADER_LENGTH);

    int offsetInternal = 0;
    this->mFormat = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;
    this->mLength = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;
    this->mLanguage = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal+= 2;
    this->mSegCount = readTwoBytesAsUShort(content + offsetInternal) / 2;
    offsetInternal+= 2;

    this->mSearchRange = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal+= 2;

    this->mEntrySelector = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal+= 2;

    this->mRangeShift = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal+= 2;
    free(content);
    content = NULL;

    uint16_t subContentLength = mLength - offsetInternal;
    uint16_t subOffset = 0;
    char* subContent = readNumberBytesFromFile(fileName, mOffset + offsetInternal, subContentLength);
    mEndCodes = (uint16_t*)malloc(sizeof(uint16_t) * mSegCount);
    for (int i = 0; i < mSegCount; ++i) {
        mEndCodes[i] = readTwoBytesAsUShort(subContent + subOffset);
        subOffset += 2;
    }
    mReservedPad = readTwoBytesAsUShort(subContent + subOffset);
    subOffset += 2;

    mStartCodes = (uint16_t*)malloc(sizeof(uint16_t) * mSegCount);
    for (int i = 0; i < mSegCount; ++i) {
        mStartCodes[i] = readTwoBytesAsUShort(subContent + subOffset);
        subOffset += 2;
    }

    mIdDeltas = (int16_t *)malloc(sizeof(uint16_t) * mSegCount);
    for (int i = 0; i < mSegCount; ++i) {
        mIdDeltas[i] = readTwoBytesAsShort(subContent + subOffset);
        subOffset += 2;
    }

    this->mIdRangeOffsetOffset = offsetInternal + subOffset;

    mIdRangeOffsets = (uint16_t*)malloc(sizeof(uint16_t) * mSegCount);
    for (int i = 0; i < mSegCount; ++i) {
        mIdRangeOffsets[i] = readTwoBytesAsUShort(subContent + subOffset);
        subOffset += 2;
    }
    free(subContent);
    subContent = NULL;

    char* segmentContent = readNumberBytesFromFile(fileName, mOffset, mLength);
    this->mRawData = (char*)malloc(sizeof(char) *(mLength + 1));
    for (int k = 0; k < mLength; ++k) {
        mRawData[k] = segmentContent[k];
    }
    mRawData[mLength] = '\0';
    free(segmentContent);
    segmentContent = NULL;
}

uint16_t SegmentMappingTable::getGlyphIndex(uint32_t characterCode){
    uint16_t  glyphIndex = 0;
    uint16_t endCode, startCode, idRangeOffset;
    int16_t idDelta;
    for (int i = 0; i < mSegCount; i++) {
        endCode = mEndCodes[i];
        if( endCode >= characterCode){
            startCode = mStartCodes[i];
            idDelta = mIdDeltas[i];
            idRangeOffset = mIdRangeOffsets[i];
            mIdRangeOffsetOffset += i * sizeof(uint16_t);
            break;
        }
    }

    if(idRangeOffset){
        int gid = 0;
        uint16_t gidOffset = idRangeOffset + mIdRangeOffsetOffset + 2 * (characterCode - startCode);
        gid = readTwoBytesAsUShort(mRawData + gidOffset);
        if(gid != 0){
            gid = (gid +  idDelta) % 65536;
        }

        glyphIndex = gid + idDelta;
    } else {
        glyphIndex = startCode + idDelta;
    }

    return glyphIndex;
}
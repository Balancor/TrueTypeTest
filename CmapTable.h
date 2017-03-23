//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_CMAPTABLE_H
#define GTRUETYPE_CMAPTABLE_H

#include "Base.h"
typedef struct {
    uint16_t 	platformID;
    uint16_t 	encodingID;
    uint32_t 	offset;
}EncodingTableRecord;

class EncodingTable : public Table {
protected:
    uint16_t 	mFormat;
    uint16_t 	mLanguage;

public:
    virtual void setOffset(uint32_t offset) = 0;
    virtual uint16_t getGlyphIndex(uint32_t charactCode) = 0;
};


class CmapTable: public Table {
protected:

    uint16_t mVersion;
    uint16_t mNumTable;
    EncodingTableRecord** mEncodingTableRecords;
    EncodingTable **mSubTables;

public:
    friend class SegmentMappingTable;
    CmapTable(const char* fileName);
    EncodingTableRecord* getEncodingRecord(uint16_t platformId, uint16_t encodingId);

    void setOffset(uint32_t offset){
        mOffset = offset;
    }

    enum {
        FORMAT_BYTE = 0,
        FORMAT_HIGH_BYTE = 2,
        FORMAT_SEGMENT = 4,
        FORMAT_TRIMMED = 6
    };
};






#endif //GTRUETYPE_CMAPTABLE_H

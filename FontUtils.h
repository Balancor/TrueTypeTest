//
// Created by guoguo on 17-4-17.
//

#ifndef GTRUETYPE_FONTUTILS_H
#define GTRUETYPE_FONTUTILS_H

#include "truetype/SegmentMappingTable.h"
#include "truetype/HeadTable.h"
#include "truetype/MaxpTable.h"
#include "truetype/LocaTable.h"
#include "truetype/HheaTable.h"
#include "truetype/HmtxTable.h"
#include "Bitmap.h"
#include "Glyph.h"
#include "truetype/ByteEncodingTable.h"

#define GLYPH_HEADER_LENGTH 10

class FontUtils {
private:
    const char *mFontFileName;

    HeadTable *mHeadTable;
    MaxpTable *mMaxpTable;
    LocaTable *mLocaTable;
    HheaTable *mHheaTable;
    HmtxTable *mHmtxTable;
    DirectoryTable *mDirectoryTable;

    SegmentMappingTable *mSegmentMappingTable;
    ByteEncodingTable *mByteEncodingTable;
    TableRecord *mGlyphTableRecord;

    int mFontSize = 16;
    int mDeviceDPI = 96;
    int mUPPEM = 0;
    float mPPEM = 0.0f;
    float mScale = 0.0f;

public:
    FontUtils(const char *fontFileName);
    void initDevInfo(int fontSize, int dpi);
    Glyph* getGlyph(uint32_t charCode);
    Bitmap *getFontbitmap(uint32_t charCode);
};


#endif //GTRUETYPE_FONTUTILS_H

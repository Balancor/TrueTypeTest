//
// Created by guoguo on 17-4-17.
//

#include "FontUtils.h"
#include "Glyph.h"
#include "truetype/GTrueType_defs.h"
#include "utils.h"

FontUtils::FontUtils(const char *fontFileName) {
    mFontFileName = fontFileName;

    mDirectoryTable = new DirectoryTable(mFontFileName);
    mHeadTable = new HeadTable(mFontFileName);
    mMaxpTable = new MaxpTable(mFontFileName);
    mLocaTable = new LocaTable(mFontFileName, mHeadTable->mIndexToLocFormat == 0 , mMaxpTable->mNumGlyphs);
    mHheaTable = new HheaTable(mFontFileName);
    mHmtxTable = new HmtxTable(mFontFileName, mHheaTable->numberOfHMetrics, mMaxpTable->mNumGlyphs);
    mGlyphTableRecord = mDirectoryTable->getTableRecord(TABLE_TAG_GLFY);
    mSegmentMappingTable = new SegmentMappingTable(mFontFileName, 3, 1);
    mByteEncodingTable = new ByteEncodingTable(mFontFileName, 3, 1);

    mUPPEM = mHeadTable->mUnitsPerEm;
}

Glyph* FontUtils::getGlyph(uint32_t charCode){
    Glyph *glyph = new Glyph(charCode);
    uint16_t gid = 0;
    if(charCode > 0 && charCode < 256){
        gid = mByteEncodingTable->getGlyphIndex(charCode);
    } else {
        gid = mSegmentMappingTable->getGlyphIndex(charCode);
    }
    uint32_t  glyphOffset = mLocaTable->getGlyphOffset(gid);
    uint32_t glyphLength = mLocaTable->getGlyphLength(gid);

    char* content = readNumberBytesFromFile(mFontFileName, mGlyphTableRecord->offset + glyphOffset, GLYPH_HEADER_LENGTH);
    int16_t numOfCountours = readTwoBytesAsUShort(content);
    if(numOfCountours >= 0){
        SimpleGlyph *simpleGlyph = new SimpleGlyph(mFontFileName, mGlyphTableRecord->offset + glyphOffset, glyphLength);
        glyph->setXMax(simpleGlyph->getMaxXCoord());
        glyph->setXMin(simpleGlyph->getMinXCoord());
        glyph->setYMax(simpleGlyph->getMaxYCoord());
        glyph->setYMin(simpleGlyph->getMinYCoord());
        glyph->initCurves(simpleGlyph->getQuadraticBezierCurves());
    } else {

    }
    return glyph;
}

void FontUtils::initDevInfo(int fontSize, int dpi){
    mFontSize = fontSize;
    mDeviceDPI = dpi;
    mPPEM = mFontSize * mDeviceDPI / 72;
    mScale = mPPEM / mUPPEM;
}


Bitmap* FontUtils::getFontbitmap(uint32_t charCode){
    Glyph* glyph = getGlyph(charCode);

    int32_t  minXCoord = glyph->getXMin();
    int32_t  minYCoord = glyph->getYMin();

    Bitmap* bitmap = new Bitmap(mPPEM, mPPEM);
    vector<QuadraticBezierCurve> curves = glyph->getQuadraticBezierCurves();
    vector<QuadraticBezierCurve>::iterator it;

    for( it = curves.begin(); it != curves.end(); it++ ){
        Point *startPoint, *controlPoint, *endPoint;
        startPoint = new Point((it->startPoint->x - minXCoord) * mScale,
                               (it->startPoint->y - minYCoord) * mScale);
        controlPoint = new Point((it->controlPoint->x - minXCoord) * mScale,
                                 (it->controlPoint->y - minYCoord) * mScale);
        endPoint = new Point((it->endPoint->x - minXCoord) * mScale,
                             (it->endPoint->y - minYCoord) * mScale);
        bitmap->drawQuadraticBezier(*startPoint, *controlPoint, *endPoint);
    }
    return bitmap;
}
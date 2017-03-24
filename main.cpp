#include <iostream>
#include "Base.h"
#include "utils.h"
#include "SegmentMappingTable.h"
#include "HeadTable.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"
using namespace std;


int main() {
    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
    uint16_t  gid = segmentMappingTable->getGlyphIndex(0x6696);
    printf("main glyph index: %u\n", gid);

    HeadTable* headTable = new HeadTable(FONT_FILENAME);
    headTable->dump();
    return 0;
}
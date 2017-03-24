//
// Created by guoguo on 17-3-21.
//

#ifndef GTRUETYPE_GTRUETYPE_DEFS_H
#define GTRUETYPE_GTRUETYPE_DEFS_H

#include <iostream>
using namespace std;

#define DIRECTORY_TABLE_LENGTH 12
#define TABLE_RECORD_LENGTH 16
#define ENCODING_TABLE_LENGTH 8
#define MAXP_TABLE_LENGTH 32
#define SEGMENT_SUBTABLE_HEADER_LENGTH 14
#define HEAD_TABLE_LENGTH 54


#define TAG_TO_ULONG(t1, t2, t3, t4) \
        (t1 & 0xFF) << 24 | (t2 & 0xFF) << 16 | \
        (t3 & 0xFF) << 8  | (t4 & 0xFF)

#define TABLE_TAG_CMAP TAG_TO_ULONG('c', 'm', 'a', 'p')
#define TABLE_TAG_GLFY TAG_TO_ULONG('g', 'l', 'y', 'f')
#define TABLE_TAG_HEAD TAG_TO_ULONG('h', 'e', 'a', 'd')
#define TABLE_TAG_HHEA TAG_TO_ULONG('h', 'h', 'e', 'a')
#define TABLE_TAG_HMTX TAG_TO_ULONG('h', 'm', 't', 'x')
#define TABLE_TAG_LOCA TAG_TO_ULONG('l', 'o', 'c', 'a')
#define TABLE_TAG_MAXP TAG_TO_ULONG('m', 'a', 'x', 'p')
#define TABLE_TAG_NAME TAG_TO_ULONG('n', 'a', 'm', 'e')
#define TABLE_TAG_POST TAG_TO_ULONG('p', 'o', 's', 't')
#define TABLE_TAG_OS_2 TAG_TO_ULONG('O', 'S', '/', '2')

//optional table
#define TABLE_TAG_CVT  TAG_TO_ULONG('c', 'v', 't', ' ')
#define TABLE_TAG_EBDT TAG_TO_ULONG('E', 'B', 'D', 'T')
#define TABLE_TAG_EBLC TAG_TO_ULONG('E', 'B', 'L', 'C')
#define TABLE_TAG_EBSC TAG_TO_ULONG('E', 'B', 'S', 'C')
#define TABLE_TAG_FPGM TAG_TO_ULONG('f', 'p', 'g', 'm')
#define TABLE_TAG_GASP TAG_TO_ULONG('g', 'a', 's', 'p')
#define TABLE_TAG_HDMX TAG_TO_ULONG('h', 'd', 'm', 'x')
#define TABLE_TAG_KERN TAG_TO_ULONG('k', 'e', 'r', 'n')
#define TABLE_TAG_LTSH TAG_TO_ULONG('L', 'T', 'S', 'H')
#define TABLE_TAG_PREP TAG_TO_ULONG('p', 'r', 'e', 'p')
#define TABLE_TAG_PCLT TAG_TO_ULONG('P', 'C', 'L', 'T')
#define TABLE_TAG_VDMX TAG_TO_ULONG('V', 'D', 'M', 'X')
#define TABLE_TAG_VHEA TAG_TO_ULONG('v', 'h', 'e', 'a')
#define TABLE_TAG_VMTX TAG_TO_ULONG('v', 'm', 't', 'x')



#define SIMPLE_GLYPH_FLAG_ON_CURVE 1
#define SIMPLE_GLYPH_FLAG_X_SHORT  1 << 1
#define SIMPLE_GLYPH_FLAG_Y_SHORT  (1 << 2)
#define SIMPLE_GLYPH_FLAG_REPEAT   1 << 3
#define SIMPLE_GLYPH_FLAG_X_SAME   1 << 4
#define SIMPLE_GLYPH_FLAG_Y_SAME   1 << 5
#define SIMPLE_GLYPH_FLAG_RESERVED1   1 << 6
#define SIMPLE_GLYPH_FLAG_RESERVED2   1 << 7

#define COMPISTE_GLYPH_FLAG_ARG_1_AND_2_ARE_WORDS 1
#define COMPISTE_GLYPH_FLAG_ARGS_ARE_XY_VALUES 1 << 1
#define COMPISTE_GLYPH_FLAG_ROUND_XY_TO_GRID 1 << 2
#define COMPISTE_GLYPH_FLAG_WE_HAVE_A_SCALE 1 << 3
#define COMPISTE_GLYPH_FLAG_RESERVED 1 << 4
#define COMPISTE_GLYPH_FLAG_MORE_COMPONENTS 1 << 5
#define COMPISTE_GLYPH_FLAG_WE_HAVE_AN_X_AND_Y_SCALE 1 << 6
#define COMPISTE_GLYPH_FLAG_WE_HAVE_A_TWO_BY_TWO 1 << 7
#define COMPISTE_GLYPH_FLAG_WE_HAVE_INSTRUCTIONS 1 << 8
#define COMPISTE_GLYPH_FLAG_USE_MY_METRICS 1 << 9
#define COMPISTE_GLYPH_FLAG_OVERLAP_COMPOUND 1 << 10
#define COMPISTE_GLYPH_FLAG_SCALED_COMPONENT_OFFSET 1 << 11
#define COMPISTE_GLYPH_FLAG_UNSCALED_COMPONENT_OFFSET << 12


#endif //GTRUETYPE_GTRUETYPE_DEFS_H

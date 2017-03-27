cmake_minimum_required(VERSION 3.6)
project(GTrueType)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GTrueType_defs.h utils.h Base.h CmapTable.cpp CmapTable.h Tables.h ByteEncodingTable.cpp ByteEncodingTable.h SegmentMappingTable.cpp SegmentMappingTable.h utils.cpp Base.cpp LocaTable.cpp LocaTable.h MaxpTable.cpp MaxpTable.h HeadTable.cpp HeadTable.h GlyphData.cpp GlyphData.h GlyphData.cpp)
add_executable(GTrueType ${SOURCE_FILES})
add_custom_command(TARGET GTrueType
        PRE_BUILD
        COMMAND cp -rp ../resources ./
        )
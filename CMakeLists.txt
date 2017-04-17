cmake_minimum_required(VERSION 3.6)
project(GTrueType)

find_package(OpenGL)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

find_package(GLUT)
if(GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIR})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp truetype/GTrueType_defs.h utils.h truetype/Base.h truetype/CmapTable.cpp truetype/CmapTable.h truetype/Tables.h truetype/ByteEncodingTable.cpp truetype/ByteEncodingTable.h truetype/SegmentMappingTable.cpp truetype/SegmentMappingTable.h utils.cpp truetype/Base.cpp truetype/LocaTable.cpp truetype/LocaTable.h truetype/MaxpTable.cpp truetype/MaxpTable.h truetype/HeadTable.cpp truetype/HeadTable.h truetype/GlyphData.cpp truetype/GlyphData.h truetype/GlyphData.cpp Bitmap.cpp Bitmap.h truetype/HmtxTable.cpp truetype/HmtxTable.h truetype/HheaTable.cpp truetype/HheaTable.h Glyph.cpp Glyph.h FontUtils.cpp FontUtils.h)
add_executable(GTrueType ${SOURCE_FILES})

target_link_libraries(GTrueType
        ${OPENGL_LIBRARIES}
        ${GLUT_glut_LIBRARY}
        ${GLEW_LIBRARIES}
        )


add_custom_command(TARGET GTrueType
        PRE_BUILD
        COMMAND cp -rp ../resources ./
        )
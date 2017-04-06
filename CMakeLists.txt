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

set(SOURCE_FILES main.cpp GTrueType_defs.h utils.h Base.h CmapTable.cpp CmapTable.h Tables.h ByteEncodingTable.cpp ByteEncodingTable.h SegmentMappingTable.cpp SegmentMappingTable.h utils.cpp Base.cpp LocaTable.cpp LocaTable.h MaxpTable.cpp MaxpTable.h HeadTable.cpp HeadTable.h GlyphData.cpp GlyphData.h GlyphData.cpp Bitmap.cpp Bitmap.h HmtxTable.cpp HmtxTable.h HheaTable.cpp HheaTable.h)
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
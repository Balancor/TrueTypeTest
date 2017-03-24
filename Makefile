CC=g++
SRC=Base.cpp \
	ByteEncodingTable.cpp \
	CmapTable.cpp \
	HeadTable.cpp \
	LocaTable.cpp \
	MaxpTable.cpp \
	SegmentMappingTable.cpp \
	main.cpp \
	utils.cpp

TrueType=TrueTypeTest
TrueType:$(SRC)
	$(CC) $(SRC) -o $(TrueType)

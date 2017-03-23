//
// Created by guoguo on 17-3-23.
//
#include "utils.h"
using namespace std;

short readTwoBytesAsShort(const char* const  content){
    short tmp = 0;
    char highByte = *content;
    char lowByte = *(content + 1);
    tmp = ((highByte << 8) & 0xFF00 | lowByte & 0xFF) & 0xFFFF;
    return tmp;
}

unsigned short readTwoBytesAsUShort(const char* const  content){
    unsigned short tmp = 0;
    char highByte = *content;
    char lowByte = *(content + 1);
    tmp = ((highByte << 8) & 0xFF00 | lowByte & 0xFF) & 0xFFFF;
    return tmp;
}

int readFourBytesAsInt(const char* const  content) {
    int tmp = 0;
    tmp = ((*content) & 0xFF) << 24 |
          ((*(content + 1)) & 0xFF) << 16 |
          ((*(content + 2)) & 0xFF) << 8  |
          ((*(content + 3)) & 0xFF);
    return tmp;
}

unsigned int readFourBytesAsUInt(const char* const  content){
    unsigned int tmp = 0;
    tmp = ((*content) & 0xFF) << 24 |
          ((*(content + 1)) & 0xFF) << 16 |
          ((*(content + 2)) & 0xFF) << 8  |
          ((*(content + 3)) & 0xFF);
    return tmp;
}
char* readFromFontFile(const char* fileName){
    FILE *fp;
    int fileLength =0;
    if(fileName != NULL){
        fp = fopen(fileName, "rt");
        if(fp){
            fseek(fp,0,SEEK_END);
            fileLength=ftell(fp);
            fclose(fp);
        }
    }

    return readNumberBytesFromFile(fileName, 0, fileLength);
}


char* readNumberBytesFromFile(const char* fileName, unsigned int offset, unsigned int count){

    FILE *fp;
    char* content=NULL;

    int fileLength =0;
    if(fileName!=NULL)
    {
        fp=fopen(fileName,"rt");
        if(fp!=NULL)
        {
            fseek(fp,0,SEEK_END);
            fileLength=ftell(fp);
            if( (offset + count) <= fileLength){
                fseek(fp, offset, 0);
                if(count>0)
                {
                    content=(char*)malloc(sizeof(char)*(count+1));
                    count=fread(content,sizeof(char),count,fp);
                    content[count]='\0';
                }
                fclose(fp);
            } else {
                cout<<"Has Error, fileLength: "<<fileLength <<
                    " is less than (offset + count) = "<< (offset + count)<<endl;
            }
        } else {
            perror("Cannot open the file: ");
        }
    }
    return content;
}
#define FONT_FILENAME "resources/MSYHMONO.ttf"


DirectoryTable* getDirectoryTable(const char* fileName){
    return new DirectoryTable(fileName);
}

CmapTable* getCmapTable(const char* fileName){
    return new CmapTable(fileName);
}

uint32_t calcTableChecksum(uint32_t *Table, uint32_t Length)
{
    uint32_t Sum = 0L;
    uint32_t *EndPtr = Table+((Length+3) & ~3) / sizeof(uint32_t);
    while (Table < EndPtr)
        Sum += *Table++;
    return Sum;
}
#include <fileReader.h>
#include <stdlib.h>

char* FileReader::Read(char *path) {
    char* text;
    FILE *pf = fopen(filename,"r");
    fseek(pf,0,SEEK_END);
    long lSize = ftell(pf);
    // 用完后需要将内存free掉
    // text=(char*)malloc(lSize+1);
    text = new char(lSize+1);
    rewind(pf); 
    fread(text,sizeof(char),lSize,pf);
    text[lSize] = '\0';
    return text;
}
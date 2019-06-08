#include <fileReader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char FileReader::Location[1024];

char* FileReader::InnerRead(char* path) {
    char fullpath[1024];
    strcpy(fullpath, FileReader::Location);
    strcat(fullpath, path);

    char* text;
    FILE *file = fopen(fullpath,"r");
    
    if(file == 0) {
        fprintf(stderr, "failed to open %s\n", fullpath);
        exit(1);
    }

    fseek(file,0,SEEK_END);
    long lSize = ftell(file);
    text = new char[lSize+1];
    rewind(file);
    fread(text,sizeof(char),lSize,file);
    text[lSize] = '\0';
    fclose(file);

    return text;
}

char* FileReader::Read(char *path) {
    return InnerRead(path);
}

char* FileReader::Read(const char *path) {
    char t[1024];
    strcpy(t, path);
    return InnerRead(t);
}

PNG* FileReader::ReadPNG(const char* path) {
    char fullpath[1024];
    strcpy(fullpath, FileReader::Location);
    strcat(fullpath, path);

    auto png = new PNG;
    stbi_set_flip_vertically_on_load(true);
    png->data = stbi_load(fullpath, &png->width, &png->height, &png->channel, 3);
    if(!png->data) {
        printf("load %s failed", fullpath);
    }

    printf("::PNG\nwid:%d\nh:%d\nchn:%d\n", png->width, png->height, png->channel);
    return png;
}

void PNG::free() {
    stbi_image_free(this->data);
}

void FileReader::Init(char* argv0) {
    auto len = strlen(argv0);
    size_t last;
    for(last=len-1;last>=0;last--) {
        if(argv0[last]=='/')
            break;
    }
    strncpy(FileReader::Location, argv0, last+1);
    // printf("Location: %s\n", FileReader::Location);
}


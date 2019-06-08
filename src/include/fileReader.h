#pragma once

struct PNG{
    int width;
    int height;
    int channel;
    unsigned char *data;

    void free();
};

class FileReader{
public:
    static void Init(char *);
    static char* Read(char*);
    static char* Read(const char*);
    static PNG* ReadPNG(const char*);
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;
private:
    FileReader();
    static char Location[1024];
    static char* InnerRead(char*);
};
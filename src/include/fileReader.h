#pragma once

class FileReader{
public:
    static char* Read(char *path);
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;
private:
    FileReader();
    
};
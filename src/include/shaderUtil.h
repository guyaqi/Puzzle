#pragma once

class ShaderUtil{
public:
    ShaderUtil(char* vsSource, char* fsSource);
    void use();

    ShaderUtil(const ShaderUtil&) = delete;
    ShaderUtil& operator=(const ShaderUtil&) = delete;
private:
    unsigned shaderProgram;

    ShaderUtil(){};
};
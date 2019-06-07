#include <shaderUtil.h>

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

ShaderUtil::ShaderUtil(char* vsSource, char* fsSource) {

    int success;
    char infoLog[512];
    
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("::vertex shader compilation failed\n%s\n::end\n", infoLog);
        exit(1);
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("::fragment shader compilation failed\n%s\n::end\n", infoLog);
        exit(1);
    }
    
    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("::shader program link failed\n%s\n::end\n", infoLog);
        exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}
void ShaderUtil::use() {
    glUseProgram(this->shaderProgram);
}
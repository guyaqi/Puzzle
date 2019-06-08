#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/vec3.hpp> 

#include <shaderUtil.h>
#include <fileReader.h>


// float vertices[] = {
//     // pos(vec3f), color(vec3f)
//     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//      0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
// };

float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

unsigned int VAO, VBO, EBO;
ShaderUtil* shader;
unsigned int texture;


void keyboard(unsigned char key, int x, int y);
void display(void);
void myInit();

int main(int argc, char** argv) {

    FileReader::Init(argv[0]);


    glutInit(&argc, argv);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Game");
    GLenum err = glewInit();
    puts("main--0--\n");

    // glutFullScreen();
    glutKeyboardFunc(&keyboard);
    puts("main--1--\n");
    myInit();
    puts("main--2--\n");
    glutDisplayFunc(&display);
    puts("main--3--\n");
    glutMainLoop(); 

    return EXIT_SUCCESS;
} 
void keyboard(unsigned char key, int x, int y) { 
    switch (key)    { 
        case 27: // ascii-esc
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

void display() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    shader->use();
    puts("display--0--\n");
    glBindTexture(GL_TEXTURE_2D, texture);
    puts("display--1--\n");
    glBindVertexArray(VAO);
    puts("display--2--\n");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    puts("display--3--\n");
    glutSwapBuffers();
}

void myInit() {

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    auto vsSource = FileReader::Read("shaders/simple.vs");
    auto fsSource = FileReader::Read("shaders/simple.fs");
    shader = new ShaderUtil(vsSource, fsSource);
    delete[] vsSource;
    delete[] fsSource;

    puts("init--0--\n");
    auto data = FileReader::ReadPNG("assets/cxk2.png");
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    puts("init--1--\n");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->width, data->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data->data);
    puts("init--2--\n");
    glGenerateMipmap(GL_TEXTURE_2D);
    data->free();
    puts("init--3--\n");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 



}
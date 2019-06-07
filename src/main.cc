#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <shaderUtil.h>
#include <fileReader.h>


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

unsigned int VAO, VBO;
ShaderUtil* shader;
// unsigned int vertexShader;
// unsigned int fragmentShader;
// unsigned int shaderProgram;

char vertexShaderSource[] = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
char fragmentShaderSource[] = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


void keyboard(unsigned char key, int x, int y);
void display(void);
void myInit();

int main(int argc, char** argv) { 
    glutInit(&argc, argv);
    
    // glutInitWindowSize(1024, 768);
    glutCreateWindow("Game");
    GLenum err = glewInit();

    // auto shader = new ShaderUtil(vertexShaderSource, fragmentShaderSource);
    // shader->use();

    glutFullScreen();
    glutKeyboardFunc(&keyboard);

    myInit();
    glutDisplayFunc(&display);  
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

    shader->use();
    // glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}

void myInit() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    char vsPath[] = "shaders/simple.vs";
    char fsPath[] = "shaders/simple.fs";
    auto vsSource = FileReader::Read(vsPath);
    auto fsSource = FileReader::Read(fsPath);
    printf("%s", vsSource);
    delete[] vsSource;
    delete[] fsSource;
    shader = new ShaderUtil(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 



}
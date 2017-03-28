//#pragma comment(lib,"libGLEW.a")

#include <GL/glew.h>

#include "textfile.h"

#include <glut/glut.h>
#include <iostream>

// GL includes
#include "Shader.h"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC



// The MAIN function, from here we start the application and run the game loop
int main(int argc, char **argv)
{
//    glutInit(&argc, argv);
    // Init GLFW
    glfwInit();
    
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // Create a GLFWwindow object that we can use for GLFW's functions
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
   Shader shader("basic.vert", "basic.frag");
    
    
    float radius = 1.0f;
    float center_x = 0.0f;
    float center_y = 0.0f;
    int vertexCount = 30;
    float PI = 3.1425;
    int idx = 0;
    // create buffer for vertex of sphere
    // float buffer[] = new float[vertexCount*2];
    glm::vec2 buffer[60];
    // Center vertex for triangle fan
//    buffer[idx++] = center_x;
//    buffer[idx++] = center_y;
    // Outer vertices of the circle
    int outerVertexCount = vertexCount-1;
    
    for (int i = 0; i < outerVertexCount; ++i){
        float percent = (i / (float) (outerVertexCount-1));
        float rad = percent * 2*PI;
        
        //Vertex position
        glm::vec2 outer;
        outer.x = outer.x  + radius * cos(rad);
        outer.y = outer.y + radius * sin(rad);
        
        buffer[idx++] = outer;
        
    }
    
    GLuint sphereVBO, sphereVAO;
    
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1,&sphereVBO);
    glBindVertexArray(sphereVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,sphereVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2) * 60 ,&buffer[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    // Generate positions
    GLfloat vertices[] = {

        //        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//        -1.0f,-1.0f, 1.0f,
//        -1.0f, 1.0f, 1.0f, // triangle 1 : end
//       
//        1.0f, 1.0f, -1.0f, // triangle 2 : begin
//        -1.0f,-1.0f, -1.0f,
//        -1.0f, 1.0f, -1.0f, // triangle 2 : end
//        1.0f, -1.0f, 1.0f // triangle 2 : end

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f

    };
    
    GLuint VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//      glUseProgram(shaderProgram);
        shader.Use();
        
        GLint projectMat = glGetUniformLocation(shader.Program,"projection_matrix");
        GLint viewMat = glGetUniformLocation(shader.Program,"view_matrix");
        GLint modelMat = glGetUniformLocation(shader.Program,"model_matrix");
        
        
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        glm::mat4 projection_matrix = glm::perspective(56.25f, 16.0f/9.0f, 0.1f, 100.0f);
//        glm::mat4 view_matrix = glm::lookAt(glm::vec3(0, 4, 4), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
        glm::mat4 view_matrix  = view;
//        glm :: mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//        glm::vec3(0.0f, 0.0f, 0.0f),
//        glm::vec3(0.0f, 1.0f, 0.0f));
//        
        glm::mat4 model_matrix; // identity
        
        glUniformMatrix4fv(projectMat, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(view_matrix));
        glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model_matrix));
        
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glDrawArrays(GL_QUADS, 0, 4);
 
//         glVertexPointer(3, GL_FLOAT, 0, vertices);
//        glDrawArrays(GL_QUADS, 0, 8);
        glBindVertexArray(0);
        
        
        glBindVertexArray(sphereVAO);
//        glDrawArrays(GL_LINE_LOOP, 2, outerVertexCount);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &sphereVBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}


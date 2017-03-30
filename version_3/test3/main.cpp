//#pragma comment(lib,"libGLEW.a")

#include <GL/glew.h>

#include "textfile.h"

#include "sphere.h"


#include <glut/glut.h>
#include <iostream>

// GL includes
#include "Shader.h"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC

bool keys[1024];
bool firstMouse = true;
GLfloat lastX = 400, lastY = 300;


glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

GLfloat yaw    = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch  =  0.0f;

void display_2()
{
    int const win_width  = 2; // retrieve window dimensions from
    int const win_height = 3; // framework of choice here
    float const win_aspect = (float)win_width / (float)win_height;
    
    glViewport(0, 0, win_width, win_height);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, win_aspect, 1, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
#ifdef DRAW_WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    sphere.draw(0, 0, -5);
    
    //    swapBuffers();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    
    GLfloat cameraSpeed = 0.05f;
    if(key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if(key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if(key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
    lastX = xpos;
    lastY = ypos;
    
    GLfloat sensitivity = 0.05;	// Change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw   += xoffset;
    pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}



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
//    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
     GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    

    
    
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    
    glewInit();
    
    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    Shader shader("basic.vert", "basic.frag");
    
    
    float radius = 0.5f;
    
    int vertexCount = 60;
    float PI = 3.1425;
    int idx = 0;
    
    
    GLfloat box[20];
    //    GLfloat box[60];
    float	step = 30.0f;
    
    //
//        float rings = 30;
//        float sectors = 10;
//        float  R = 1./(float)(rings-1);
//        float  S = 1./(float)(sectors-1);
//        float  PI2 = PI/2;
//        glm::vec3 buffer[900];
//        glm::vec3 outer;
//    //
//        for(int r = 0; r < rings; ++r) {
//            for(int s = 0; s < sectors; ++s) {
//              //             glm::vec3 outer;
//                printf("index : %d \n", idx);
//                outer.x = cos(2*PI * s * S) * sin( PI * r * R );
//                outer.y = sin( -PI2 + PI * r * R );
//                outer.z = sin(2*PI * s * S) * sin( PI * r * R );
//    //            float const y = sin( -M_PI_2 + PI * r * R );
//    //            float const x = cos(2*PI * s * S) * sin( PI * r * R );
//    //            float const z = sin(2*PI * s * S) * sin( PI * r * R );
//    
//                buffer[idx] = outer;
//                idx = idx + 1;
//    
//            }
//    //        idx = idx + 1;
//        }
    
    //angleInDegrees * Math.PI / 180
//    int buffercount = 7;
    glm::vec3 buffer[6000];
    int buffercount = 6000;
    glm::vec3 outer;
    float section = 10.0f;
    GLfloat  alpha, beta;
    //    GLfloat RR = gradation * PI / 180;
    int index = 0;

    for (beta = 0.0; beta < 2.01* PI; beta += PI/section)
    {
        
        for (alpha = 0.0 ; alpha < PI; alpha += PI/section)
        {

            outer.x = radius*cos(beta)*sin(alpha);
            outer.y = radius*sin(beta)*sin(alpha);
            outer.z = radius*cos(alpha);

            printf("index:%d \n", index);
            buffer[index] = outer;
            index = index +1;
        }
        
    }
 
//    for (alpha = 0.0 ; alpha <= PI; alpha += PI/section)
//    {
//        printf("alpha : %f \n ",alpha );
//        for (beta = 0.0 ; beta <= 2.01* PI; beta += PI/section)
//        {
//            
//            outer.x = radius*cos(beta)*sin(alpha);
//            outer.y = radius*sin(beta)*sin(alpha);
//            outer.z = radius*cos(alpha);
//            
////            printf("index:%d \n", index);
//            buffer[index] = outer;
//            index = index +1;
//
//        }
//        
//    }
//
    // ----------
    
    //-----------
    GLuint sphereVBO, sphereVAO;
    
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1,&sphereVBO);
    glBindVertexArray(sphereVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,sphereVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*index  ,&buffer[0], GL_STATIC_DRAW);
    
    //    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * 360 ,&box[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    //    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
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
        
        
               
//        SolidSphere sphere(1, 12, 24);
//        
//        display_2;
//        
        GLint projectMat = glGetUniformLocation(shader.Program,"projection_matrix");
        GLint viewMat = glGetUniformLocation(shader.Program,"view_matrix");
        GLint modelMat = glGetUniformLocation(shader.Program,"model_matrix");

        
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        // view matrix
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //        glm::mat4 view_matrix = glm::lookAt(glm::vec3(0, 4, 4), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
        glm::mat4 view_matrix  = view;
        //        glm :: mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
        //        glm::vec3(0.0f, 0.0f, 0.0f),
        //        glm::vec3(0.0f, 1.0f, 0.0f));

        
        // projection matrx
        glm::mat4 projection_matrix = glm::perspective(56.25f, 16.0f/9.0f, 0.1f, 100.0f);
        
        
        // model matrix
        glm::mat4 model_matrix; // identity
        
        glUniformMatrix4fv(projectMat, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(view_matrix));
        //        glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model_matrix));
        
        
        glBindVertexArray(VAO);
        glBindVertexArray(0);
        
        
        glBindVertexArray(sphereVAO);
        //        glDrawArrays(GL_LINE_LOOP, 2, outerVertexCount);
        for (GLuint i = 0; i < index; i++)
        {
            
            glm::mat4 model;
            model = glm::translate(model, buffer[i]);
            GLfloat angle = 10.0f * i;
//            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::rotate(model, angle, glm::vec3(1.0f ,-4.0f, 0.5f));
            glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model));
             glDrawArrays(GL_TRIANGLES, 0, 10);
        }
        
//        GL_LINE_STRIP  GL_TRIANGLE_STRIP
//        glDrawArrays(GL_TRIANGLE_FAN, 0, 900);
        
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


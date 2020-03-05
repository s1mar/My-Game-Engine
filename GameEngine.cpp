// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
const GLint WIDTH = 1440, HEIGHT = 900; //Window dimensions
const char* TITLE = "It Lives";
GLFWwindow* WINDOW;

bool initializeWindow();
void fpsCounter();

const float FPS_TEXT_UPDATE_FREQUENCY = 0.25f;

void drawTriangle() {}


//Shader Section//
const GLchar* vertexShader = "#version 330 core\n layout(location = 0) in vec3 position;\nvoid main(){\ngl_position = vec4(position.x,position.y,position.z,1.0);\n}";
const GLchar* fragmentShaderSrc

int main()
{
    if (!initializeWindow()) {
        std::cerr << "Failed initializing the window, please see the console for error details" << std::endl;
        //Just to be sure that the clean-up happened
        glfwTerminate();
        return 1;
    }

    return 0;
}

bool initializeWindow() {
    
    //Init GLFW
    if (!glfwInit()) {
        printf("GLFW init failed");
        glfwTerminate(); //terminating any remnant glfw artifacts
        return false; //telling the kernel that the operation failed;
    }


    //setting properties of the glfw window that I'm going to create after this

    //OpenGl version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Since a lot of things were modernized after opengl 3.2, I don't want to use any legacy code. So, enforcing it to use only 3.3 and upwards
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No Backwards compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Forward Compatibility allowed

    //Creating the window
     WINDOW = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if (!WINDOW) {

        printf("The operation to create the window failed");
        //clean-up
        glfwTerminate();
        return false;
    }

    //setting up the buffer to the window
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(WINDOW, &bufferWidth, &bufferHeight);

    //Setting up context for glfw, letting it know as to which window stuff is being drawn to by openGL
    glfwMakeContextCurrent(WINDOW); //When the context if being set, it's default set to the width and height of the window

    //Setting up GLEW
    //Enabling modern extension features
    glewExperimental = GL_TRUE;

    //Initializing GLEW
    if (glewInit() != GLEW_OK) {
        printf("Glew init failed");
        glfwDestroyWindow(WINDOW);
        glfwTerminate();
        return false;
    }

    //setting up the viewport, part of the window that I'm drawing to, for this case, I'm just gonna draw on the whole thing
    glViewport(0, 0, bufferWidth, bufferHeight);

    //setting up a loop that will keep on looping until the window is closed

    //An example of it closing is when I press the close button on the window. I can use this as a game loop for now

    //Setting up key input
    
    //Will also close when the END button is pressed; This has to be defined here before I go onto the next loop polling for events.Otherwise, this won't work

    glfwSetKeyCallback(WINDOW, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

        if (key == GLFW_KEY_END && action == GLFW_PRESS) {
            printf("End key pressed");
            glfwSetWindowShouldClose(window, GL_TRUE);        //closing the window when the end key is pressed on the keyboard
        }
        });

    while (!glfwWindowShouldClose(WINDOW)) {

        //Polling for user triggered input events
        glfwPollEvents();

        //This will show the fps on the title bar
        fpsCounter();
        
        //Clear Window
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(WINDOW); //Like the Professor said, there are 2 buffers, one that is drawn and that the other that we are drawing to, so we just swap them to show the one that we've just drawn to
    }
    return true;
}

void fpsCounter() {
                             
   //to get the fps, I need to keep track between prev and current renders
    static double prevTimeInSeconds = 0.0;
    static int countOfFrames = 0;

    double timeElaspedInSeconds;
    double currentTimeInSecs = glfwGetTime(); //since I haven't used glfwSetTime, this should return the time since GLFW got initialized and started


    timeElaspedInSeconds = currentTimeInSecs - prevTimeInSeconds;

   
    if (timeElaspedInSeconds > FPS_TEXT_UPDATE_FREQUENCY)
    {
      
        prevTimeInSeconds = currentTimeInSecs;
        double framePerSec = (double)countOfFrames / timeElaspedInSeconds;

        //Setting the window title
        ostringstream outs;
        outs.precision(2);	// setting the precision to 2 decimal places
        outs << fixed << TITLE << "  Fps: " << framePerSec;
        
        glfwSetWindowTitle(WINDOW, outs.str().c_str()); //I wanted to use data but since the function signature wants a char* pointer, using c_str()

        
        //Resetting for the next one
        countOfFrames = 0;
    }

    countOfFrames++;

}

void drawTriangle() {
   
    GLfloat vertices[] = {
    0,0.5f,0,
    -0.5,0,0,
    0.5,0,0
    };
 
    GLuint vertexBufferObject; //the vbo object
    glGenBuffers(1, &vertexBufferObject); //creating one buffer and saving it's address in the vbo object above
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject); //since the vertices are type of array, I'm using GL_ARRAY_BUFFER
    //Note: In openGl we can only have one buffer active at a time
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since the vertice data won't be changed a lot, I'm sticking with STATIC_DRAW instead of DYNAMIC_DRAW

    //Core openGL now requires vertex array objects to draw
    GLuint vertexArrayObject; //the vao
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject); //to make the vao the active one, so that I can setup the attrib pointer
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, NULL); //the first is zero for I only have position data

    glEnableVertexAttribArray(0); //By default openGL disables this array, I'm enabling it


    //What to put inside the loop later
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //After drawing the points, unhook it
    glBindVertexArray(0);


}

struct primitive {
    GLfloat vertices[];
};
// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;
const GLint WIDTH = 1440, HEIGHT = 900; //Window dimensions
const char* TITLE = "It Lives";



GLFWwindow* WINDOW;
GLuint SHADER_PROGRAM;
GLuint VERTEX_ARRAY_OBJECT,VERTEX_BUFFER_OBJECT,ELEMENT_BUFFER_OBJECT;
bool IS_WIREFRAME_VISIBLE;


bool initializeWindow();
bool initializeShaderProgram();
void fpsCounter();
void initializePrimitivesToDraw();
void startTheGameLoop();
void postRunCleanUp();
void initTranslationDemo();
void translationDemo();

//For Basic translation demo
GLuint y_move;
bool currentTranslationDirectionUp = true;

//Simple Logic: With each loop I'm going to increment by the offsetIncrement and when my primitives will hit the maxoffset, 
//I'm going to reverse directions and this process will keep on looping
float translationOffset = 0.0f, maxTranslationOffset = 0.65f, offsetIncrement = 0.0025f;

const float FPS_TEXT_UPDATE_FREQUENCY = 0.25f;

//Shader Defined Section//
//These are the two minimum required shader
const GLchar* vertexShaderSrc =   "#version 330 core\n layout(location = 0) in vec3 position;\nlayout (location = 1) in vec3 color;\nout vec3 vertColor; \nuniform float movY;\nvoid main(){\nvertColor = color;\ngl_Position = vec4 (position.x,position.y+movY,position.z,1.0);\n}";
const GLchar* fragmentShaderSrc = "#version 330 core\n out vec4 color;\nin vec3 vertColor;\nvoid main(){\ncolor = vec4 (vertColor,1.0f);\n} ";


int main()
{
    //Intitialize the main window
    if (!initializeWindow()) {
        std::cerr << "Failed initializing the window, please see the console for error details" << std::endl;
        //Just to be sure that the clean-up happened
        glfwTerminate();
        return 1;
    }

    //Initialize the shaders
    if (!initializeShaderProgram()) {
        std::cerr << "Failed initializing the shaders, please see the console for error details" << std::endl;
        //Just to be sure that the clean-up happened
        glfwTerminate();
        return 1;
    }

    initializePrimitivesToDraw();
    initTranslationDemo();
    startTheGameLoop(); //post run cleanup is encapuslated inside this method, so as soon as it ends, the clean-up is gonna take place

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
        else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
            
            printf("Toggling wireframe");
            IS_WIREFRAME_VISIBLE = !IS_WIREFRAME_VISIBLE;
            if (IS_WIREFRAME_VISIBLE) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

        }
   });

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



void startTheGameLoop() {
    while (!glfwWindowShouldClose(WINDOW)) {

        //Polling for user triggered input events
        glfwPollEvents();

        //This will show the fps on the title bar
        fpsCounter();

        //Clear Window
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Drawing my triangle one --START
        glUseProgram(SHADER_PROGRAM);
        translationDemo();
        glBindVertexArray(VERTEX_ARRAY_OBJECT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //After drawing the points, unhook it
        glBindVertexArray(0);
        //Drawing my triangle --END

        glfwSwapBuffers(WINDOW); //Like the Professor said, there are 2 buffers, one that is drawn and that the other that we are drawing to, so we just swap them to show the one that we've just drawn to

    }

    postRunCleanUp();

}


bool initializeShaderProgram() {
    //Shader init
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);


    //check if the shader compiles good
    GLint result;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if (!result) {

        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        printf("Vertex Shader compilation failed:" + *infoLog);
        return false;
    }

    //Now checking compilation for the fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        printf("Fragment shader compilation failed:" + *infoLog);
        return false;
    }

    //Creating a shader program to use the shader
    SHADER_PROGRAM = glCreateProgram();
    glAttachShader(SHADER_PROGRAM, vertexShader);
    glAttachShader(SHADER_PROGRAM, fragmentShader);
    glLinkProgram(SHADER_PROGRAM);

    glGetProgramiv(SHADER_PROGRAM, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(SHADER_PROGRAM, sizeof(infoLog), NULL, infoLog);
        printf("Shader program linking failed:" + *infoLog);
        return false;
    }
    //Now since the program is created, I can delete the shaders
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    return true;

}

void initTranslationDemo() {
    //Code for basic translation demo
    y_move = glGetUniformLocation(SHADER_PROGRAM, "movY");
}

//run inside the game loop; note to self: remember to place it after I set the shader program
void translationDemo() {
    if (abs(translationOffset) >= maxTranslationOffset) {
            //reverse the translation direction
        currentTranslationDirectionUp = !currentTranslationDirectionUp;
    }

    translationOffset = (currentTranslationDirectionUp) ? translationOffset + offsetIncrement : translationOffset - offsetIncrement;
    glUniform1f(y_move, translationOffset);
}

void initializePrimitivesToDraw() {

    //Triangle one has position as well as color data for the vertices
    GLfloat vertices[] = {
        //triangle one data
        -0.5f,0.5f,0.0f,   1.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,      //the common vertice that both the triangles share
       -0.5f,-0.5f,0.0f,   0.0f,0.0f,1.0f,

       //triangle two data
        0.5f,0.5f,0.0f,   0.0f,0.0f,1.0f,
        0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f
    };

    //Since both the primitive triangles share one common vertice, I'm going to use now and element buffer object to construct or render the primitives
    GLint indexes[] = {
        //triangle one is constructed using
        0,1,2,
        //triangle two is made up of
        3,1,4
    };


    //Triangle One Init
    glGenBuffers(1, &VERTEX_BUFFER_OBJECT); //creating one buffer and saving it's address in the vbo object above
    glBindBuffer(GL_ARRAY_BUFFER, VERTEX_BUFFER_OBJECT); //since the vertices are type of array, I'm using GL_ARRAY_BUFFER
    //Note: In openGl we can only have one buffer active at a time
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since the vertice data won't be changed a lot, I'm sticking with STATIC_DRAW instead of DYNAMIC_DRAW

    //Core openGL now requires vertex array objects to draw
    glGenVertexArrays(1, &VERTEX_ARRAY_OBJECT);
    glBindVertexArray(VERTEX_ARRAY_OBJECT); //to make the vao the active one, so that I can setup the attrib pointer

    //Attrib pointer for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, NULL); //the first is zero for I only have position data. A float is of 4 bytes and since we have x,y,z to represent a vertice. 

    //Attrib pointer for color 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)(sizeof(GLfloat) * 3)); //Since the color attribs are after the first 3 float positions

    glEnableVertexAttribArray(0); //By default openGL disables this array, I'm enabling it
    glEnableVertexAttribArray(1); //Enabling my color pointer as well


    //Setting up the element buffer
    glGenBuffers(1, &ELEMENT_BUFFER_OBJECT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ELEMENT_BUFFER_OBJECT);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
}

void postRunCleanUp() {
    //post run clean-up
    glDeleteProgram(SHADER_PROGRAM);
    glDeleteVertexArrays(1, &VERTEX_ARRAY_OBJECT);
    glDeleteBuffers(1, &VERTEX_BUFFER_OBJECT);
    glDeleteBuffers(1, &ELEMENT_BUFFER_OBJECT);
    glfwTerminate();
}




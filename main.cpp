#define GLEW_STATIC
#include<glew.h>
#include <glfw3.h>

#include "game_controller_h.h"
#include "res_manager_h.h"



//The window title
const char* TITLE = "POOJA: DEMO 2D - BREAKOUT CLONE";
//The Width and Height of the screen
const GLuint SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 768;

//The GameController handles the game logic 
GameController mGController(SCREEN_WIDTH, SCREEN_HEIGHT);

//The callback to process key inputs
void callback_KeyInput(GLFWwindow* window, int key, int scancode, int action, int mode);
void fpsCounter(GLFWwindow* window);

int main(int argc, char* argv[])
{
    //OpenGl version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    //Since a lot of things were modernized after opengl 3.2, I don't want to use any legacy code. So, enforcing it to use only 3.3 and upwards
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    if (!glfwInit()) {
        printf("GLFW initialization failed");
        glfwTerminate(); //terminating any remnant glfw artifacts
        return 1; 
    }
  
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, nullptr, nullptr);

    if (window == nullptr) {
        printf("The operation to create the Window failed");
        //clean-up
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
    //To handle resizing of the window, I must set the glViewport again
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {

        printf("Glew initialization failed");
        glfwDestroyWindow(window);
        glfwTerminate();

    };


    glGetError(); // It's a good practice to call it once to catch glewInit() bug if it's there.

    glfwSetKeyCallback(window, callback_KeyInput);

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initializing the game
    mGController.Initialize(); //It'll be intialized with the MENU state

    //The DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    //Setting up the game loop
    while (!glfwWindowShouldClose(window))
    {
        // Calculating delta time
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        fpsCounter(window);
        
        // Managing user input
        mGController.InputProcessing(deltaTime);

        // Updating the Game state
        mGController.Update(deltaTime);

        //Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mGController.Render();

        glfwSwapBuffers(window);
    }

    //Post run clean-up
    // Delete all resources as loaded using the resource manager
    ResManager::CleanUp();
    glfwTerminate();
    return 0;
}

void callback_KeyInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_X) && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            mGController.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            mGController.keys[key] = GL_FALSE;
    }
}

void fpsCounter(GLFWwindow* window) {

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
        outs << fixed << TITLE << "                          Fps: " << framePerSec;

        glfwSetWindowTitle(window, outs.str().c_str()); //I wanted to use data but since the function signature wants a char* pointer, using c_str()


        //Resetting for the next one
        countOfFrames = 0;
    }

    countOfFrames++;

}

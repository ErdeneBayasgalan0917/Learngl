/*
I sincerely apoligize to whoever has decided to read this. I am sorry for the swearing, the profanity and the lack of manners and common human sense. 
I am dealing with uni and other fields of development while learning opengl. goodluck.
and if im available (goodluck with that) feel free to ask me questions
*/


// P.S. DONT CALL FUNCTIONS IN INT MAIN YOU FUCKING IDIOT
// so many hours..... so many. just for include. anyways, dont ask me how i did it. i just did. if you got here, you can do the rest.
#include <iostream>
#include "glad/glad.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// --- Globals for fullscreen toggle ---
bool isFullscreen = true;
const int WINDOWED_WIDTH = 1280;
const int WINDOWED_HEIGHT = 720;


// Callback function for window resize(aka code magic)
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Handles all key presses.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Close window on escape
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Toggle fullscreen on F11
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
	{
		isFullscreen = !isFullscreen;
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (isFullscreen)
		{
			// Go to borderless fullscreen
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
			glfwSetWindowSize(window, mode->width, mode->height);
			glfwSetWindowPos(window, 0, 0);
		}
		else
		{
			// Go to windowed mode
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
			glfwSetWindowSize(window, WINDOWED_WIDTH, WINDOWED_HEIGHT);
			// Center the window
			int xpos = (mode->width - WINDOWED_WIDTH) / 2;
			int ypos = (mode->height - WINDOWED_HEIGHT) / 2;
			glfwSetWindowPos(window, xpos, ypos);
		}
	}
}

// OpenGL error checking helper function
GLenum glCheckError_(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}



#ifdef _DEBUG
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#else
#define glCheckError() ((void)0)
#endif



int main() {
	// Initialize GLFW [DO NOT TOUCH IT YOU FUCKING MASOCHIST]
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Set OpenGL version (3.3 Core) [so important. DONT TOUCH IT]
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Enable OpenGL debug context for better error reporting
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	// --- Windowed Fullscreen (Borderless) Setup ---
	// This avoids the screen flashing from exclusive fullscreen mode.
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Make it borderless

	// Create window [not as bad but still, dont play with this except the numbers. you wont understand the rest anyways]
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Register our new key callback
	glfwSetKeyCallback(window, key_callback);
	

	// Load OpenGL functions using GLAD [if glad not working = throw error]
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	
	

	// Set the callback for window resize 
	//[this has to be called every time the windows changes size or the user change the size. hmmm i dont have anything to see so i cant test it]
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	
	//vertices. noice. before the render loop but still in int main.
	// TRIANGLE
	float vertices[] = { // vertex attributes for a single vertex are now position and color
		// positions         // colors
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left
		 0.5f, -0.5f, 0.0f,  0.0f, 0.5f, 0.5f,  // bottom right 
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top center 
	}; //dont forget semicolons. please. SEMICOLONS ;;; SHALL RULE THE WORLD
	
	//VBO setup
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//GLSL
	const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
	layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

	uniform mat4 transform; // Our new transformation matrix

	out vec3 ourColor; // output a color to the fragment shader

	void main() {
	    gl_Position = transform * vec4(aPos, 1.0); // Apply the transformation
		ourColor = aColor;
	}
	)";


	const char* fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;

	in vec3 ourColor; // we retrieve the color from the vertex shader (it's interpolated!)

	void main() {
	FragColor = vec4(ourColor, 1.0f);
	}
	)";
	//compiled at run-time (why?? isnt that overhead? any other way???)



	//Shader setup (vertex)
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile shader
	glCompileShader(vertexShader);
	//compile success check
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if unsuccessful, output error message and error log
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	



	// Fragment Shader compile 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Shader program
	//compile success check
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram; //initialize
	shaderProgram = glCreateProgram(); //Create program
	glAttachShader(shaderProgram, vertexShader); //attach vertex shader
	glAttachShader(shaderProgram, fragmentShader); //attach fragment shader
	glLinkProgram(shaderProgram); //link program
	//Debug linking program linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders after attaching and linking since they are no longer needed
		glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// 1. bind the Vertex Array Object first. This "captures" the following VBO and attribute pointer configurations.
	glBindVertexArray(VAO);

	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. then set the vertex attributes pointers.
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// You can unbind the VBO now. The VAO has remembered that the attribute at location 0 is sourced from this VBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Get the location of our new uniform. This should be done once.
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

	
	// MAIN RENDER LOOP [what if we could implement intentional lag into our game ehehehehhe]


	// MAIN RENDER LOOP [what if we could implement intentional lag into our game ehehehehhe]
	while (!glfwWindowShouldClose(window)) {
		// Set background color and clear

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  //pure black. standard protocol
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		WTF IS A BIT AND WHY IS IT FROM A BUFFER
		CLEAR BUFFER????? WHAT IS THAT v1

		oh so a buffer is just a artifact of the gpu. it stores the pixel data. depth buffer for 3d depth(distance from viewer) data
		color buffer is for well.. color. cmon. and stencil buffer. I have no idea. masking data it says. what is that??? v2

		ooohhhhh. masking data. literally masking data. like a stencil or a drawing template. like how artists use masking tape to cover the edges of 
		their canvases. makes so much sense now. v3

		*/

		// Activate the shader program
		glUseProgram(shaderProgram);

		// === THIS IS WHERE THE ANIMATION MATH GOES! ===
		// Create a transformation matrix. Start with an identity matrix (one that does nothing).
		glm::mat4 transform = glm::mat4(1.0f); 
		// Rotate it over time around the Z-axis. glfwGetTime() gives us a smoothly increasing value.
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.25f, 0.5f, 1.0f));

		// Send the matrix to the shader
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Now, draw the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		
		
		

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
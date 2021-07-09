#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


static int WIDTH = 1280;
static int HEIGHT = 1080;

void OnResize(GLFWwindow* window, int width, int height)
{
	// Resize the viewport
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, WIDTH, HEIGHT);
}

void ProcessInput(GLFWwindow* window)
{
	// If escape key is pressed, send the signal to close the window and stop
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void LogGLdebugMess(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* UserParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		return;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "in line :" << UserParam;
		std::cout << std::endl;
	}
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BSPRenderingEngine", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Making the current window as render context
	glfwMakeContextCurrent(window);


	//Initializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Initialize GLAD" << std::endl;
		return -1;
	}

	/*glenable(gl_debug_output);
	glenable(gl_)

		gldebugmessagecallback();*/
	//Creating viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetFramebufferSizeCallback(window, OnResize);


	// Shader Creation
	const char* vertexShaderSource = "#version 430 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 430 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char info[1000];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1000, NULL, info);

		std::cout << "Error in VertexShader \n" << info;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1000, NULL, info);
		std::cout << "Error in FragmentShader \n" << info;
	}

	unsigned int program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Render a Triangle
	float vertices[8] = {
							-0.75f, -0.75f,
							0.25f, -0.25f,
							0.25f, 0.25f,
							-0.75f, 0.75f
	};

	unsigned int indices[6] = { 0, 1, 3, 3, 1, 2 };

	// Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int elementBuffer;
	glGenBuffers(1, &elementBuffer);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Main Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glUseProgram(program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}




























































/*
static int WIDTH = 1080 , HEIGHT = 1280;

void onResize(GLFWwindow* window, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, WIDTH - 20, HEIGHT - 20);
}

void ProcessInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE)== GLFW_PRESS)
	(glfwSetWindowShouldClose(window,true));
}

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BSPEngine", NULL, NULL);

	if (!window)
	{
		std::cout << "GLAD didnt load" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//GLAD initializer
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed load" << std::endl;
		return -1;
	}

	//creating viewport
	glad_glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, onResize);


	//Shader Creation
	const char* vertexShaderSource = "#version 430 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";
		
	const char* fragmentshaderSource= "#version 430 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"}\0";

	unsigned int Vshader = glCreateShader(GL_VERTEX_SHADER),Fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glGetShaderSource(Vshader, 1, &vertexShaderSource, NULL);
	glCompileShader(Vshader);

	unsigned int Fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fshader, 1, &fragmentshaderSource, NULL);
	glCompileShader(Fshader);
	//render a triangle
	float Vertices[12] = {
	-.25f, -.25f,
	.25f,-.25f,
	-.25f, .25f,
	-.25f,.25f,
	.25f,-.25f,
	.25f,.25f
	};
	
	//vertex buffer objects
	unsigned int VBO,VAO,elementbuffer;
	glGenBuffers(1, &VBO);	//container which stores array of data
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);


	/* for reading PTN data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)12);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)20);
	
	//main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}*/


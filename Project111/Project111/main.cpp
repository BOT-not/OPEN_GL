#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	*/
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
}
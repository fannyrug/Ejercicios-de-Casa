/*---------------------------------------------------------*/
/* ----------------   Prática 2 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computacion Gráfica e interacción humano computadora---------------*/
/*------------- Visual Studio 2017  ---------------------------*/
//RUGERIO FERNANDEZ COBOS FANNY 

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint shaderProgramRed, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec4 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";


static const char* myFragmentShaderRed = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(3.0f, 4.0f, 4.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{


	float vertices[] =
	{
		// positions         //
		//C de Cobos 
		-0.8f, 0.8f, 0.0f, 0.0f, 0.255f, 0.255f,     //poscion, color a
		-0.2f, 0.8f, 0.0f,  0.0f, 0.128f, 0.0f,     //poscion, color b
		-0.2f, 0.6f, 0.0f,  0.0f, 0.128f, 0.0f, //poscion, color c
		-0.6f, 0.6f, 0.0f,  0.128f, 0.0f, 0.0f, //poscion, color d
		-0.6f, -0.6f, 0.0f, 0.255f, 0.127f, 0.80f, //poscion, color e
		-0.2f, -0.6f, 0.0f,  0.423f, 0.86f, 0.53f, //poscion, color f
		-0.2f, -0.8f, 0.0f,  0.255f, 0.140f, 0.0f,//poscion, color g
		-0.8f, -0.8f, 0.0f,	0.27f, 0.42f, 0.85f, //poscion, color h
		/// F de Fanny 
		 0.2f, 0.8f, 0.0f, 0.128f, 0.0f, 0.0f,     //poscion, color 8
		 0.8f, 0.8f, 0.0f,  0.0f, 0.128f, 0.128f,     //poscion, color 9
		 0.8f, 0.6f, 0.0f,  0.5f, 0.3f, 0.7f, //poscion, color 10
		 0.4f, 0.6f, 0.0f,  0.8f, 0.2f, 0.1f, //poscion, color 11
		 0.4f, 0.1f, 0.0f, 0.5f, 0.3f, 0.2f, //poscion, color 12
		 0.8f, 0.1f, 0.0f,  0.64f, 0.123f, 0.42f, //poscion, color 13 
		 0.8,  -0.1f, 0.0f,  0.23f, 0.43f, 0.0f, //poscion, color 14
		 0.4f, -0.1f, 0.0f,	0.128f, 0.0f, 0.0f, //poscion, color 15
		0.4f, -0.8f, 0.0f,  0.0f, 0.128f, 0.128f, //poscion, color 16 
		0.2f, -0.8f, 0.0f, 0.432f, 0.3f, 0.4f, //poscion, color 17
		 
	};

	unsigned int indices[] =
	{
		//INDICES PARA LETRA C
		0, 1, 3,
		1, 2, 3,
		0, 3, 4,
		0, 7, 4,
		4, 5, 6,
		7, 4, 6,
		// INDICES PARA LETRA F
		
		
		8, 9, 10,//ok
		8,11,10, //ok
		8,11,16,
		8,17,16,
		13,15,14, 
		12,15,14,
		12,13,14,
		//16,17,8,
		};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRed, 1, &myFragmentShaderRed, NULL);
	glCompileShader(fragmentShaderRed);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometr僘 con Color
	shaderProgramRed = glCreateProgram();
	glAttachShader(shaderProgramRed, vertexShader);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 


	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderRed);
	glDeleteShader(fragmentShaderColor);

}

void display(void)
{
	glUseProgram(shaderProgramColor);

	glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glPointSize(5.0);
	glDrawElements(GL_TRIANGLE_FAN, 12, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(12 * sizeof(GLuint)));
	glDrawElements(GL_TRIANGLE_FAN, 12, GL_UNSIGNED_INT, BUFFER_OFFSET(18 * sizeof(GLuint)));
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(30 * sizeof(GLuint)));
	

	glBindVertexArray(0);

	glUseProgram(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	//Configurar Shaders
	setupShaders();


	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(3.3f, 3.3f, 4.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}
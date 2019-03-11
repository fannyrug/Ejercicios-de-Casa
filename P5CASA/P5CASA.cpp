



#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float movX = 0.0f;
float movY = 0.0f:
float movZ = -5.0f;
float rotX = 0.0f;
float rotY = 0.0f;

float angHom = 0.0f;
float angHomIzq = 0.0f;
float angCo = 0.0f;
float angMu = 0.0f;
float angPu = 0.0;
float angIn = 0.0f;
float angMed = 0.0f;
float angAn = 0.0f;
float angMe = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection


	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

	//CABEZA
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(1.5f, 2.5f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.9f, 0.0f, 0.1f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); // A lonely cube :(

	//CUELLO 
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(0.5f, 0.5f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.9f, 0.0f, 0.1f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//TRONCO
	model = glm::translate(model, glm::vec3(0.0f, -2.75f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(4.0f, 5.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//CADERA
	model = glm::translate(model, glm::vec3(0.0f, -3.5f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(4.0f, 2.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.9f, 1.0f, 0.1f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//PIERNA IZQ.
	model = glm::translate(model, glm::vec3(-1.5f, -2.5f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(1.0f, 3.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24);  //A lonely cube : (

	//PIE IZQ.
	model = glm::translate(model, glm::vec3(-1.5f, -2.0f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(4.0f, 1.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 0.2f, 0.0f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//PIE DER.
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(4.0f, 1.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 0.2f, 0.0f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//PIERNA DER.
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, 0.0f));
	modelTemp = model;
	modelTemp = glm::scale(modelTemp, glm::vec3(1.0f, 3.0f, 1.0f));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", modelTemp);
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (

	//HOMBRO DER.
	model = glm::translate(model, glm::vec3(1.0f, 8.0f, 0.0f));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 0.9f, 0.4f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 0, 1));

	//BICEP DER.
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.4f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//ANTEBRAZO DER. 
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(angCo), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//PALMA DER.
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(angMu), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.8f, 0.0f)); 
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;
	modelTemp2 = model;

	//PULGAR DER. 
	model = glm::translate(model, glm::vec3(-0.35f, 0.5f, 0.0f)); 
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0)); 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//PULGAR DER. 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0)); 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.4f, 0.7f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//INDICE DER. 
	model = glm::translate(model, glm::vec3(0.5f, 0.38f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0.0, -1.0, 0.0)); 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3f, 0.25f, 0.3f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.4f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//INDICE DER. 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.4f, 0.0f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24);//A lonely cube : (
	model = modelTemp;

	//INDICE DER. 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.4f, 0.0f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//MEDIO DER. 
	model = glm::translate(model, glm::vec3(0.5f, 0.13f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEDIO DER.
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEDIO DER. 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//ANULAR DER. 
	model = glm::translate(model, glm::vec3(0.5f, -0.12f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//ANULAR DER. 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);//A lonely cube : (
	model = modelTemp;

	//ANULAR DER. 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//MEÑIQUE DER. 
	model = glm::translate(model, glm::vec3(0.5f, -0.37f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24);//A lonely cube : (
	model = modelTemp;

	//MEÑIQUE DER.
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEÑIQUE DER. 
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe*0.7f), glm::vec3(0, -1, 0)); 
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24);//A lonely cube : (

	//HOMBRO IZQ. 
	modelTemp = glm::mat4(1.0f);
	model = modelTemp; 

	model = glm::translate(model, glm::vec3(-2.0, -2.25, 0));
	model = glm::translate(model, glm::vec3(-0.5, 0.0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 0.9f, 0.4f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = glm::rotate(model, glm::radians(-angHom), glm::vec3(0, 0, 1));

	//BICEP IZQ.
	model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.4f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//ANTEBRAZO IZQ. 
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(-angCo), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//PALMA IZQ.
	model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(-angMu), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.8f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;
	modelTemp2 = model;

	//PULGAR IZQ. 
	model = glm::translate(model, glm::vec3(0.35f, 0.5f, 0.0f)); 
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0)); 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//PULGAR IZQ. 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0)); 
	model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.4f, 0.7f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//INDICE IZQ. 
	model = glm::translate(model, glm::vec3(-0.5f, 0.38f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.4f,0.0f,0.1f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//INDICE IZQ.
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.4, 0.0, 0.1));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//INDICE IZQ.
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.4f, 0.0f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24);//A lonely cube : (
	model = modelTemp2;

	//MEDIO IZQ. 
	model = glm::translate(model, glm::vec3(-0.5f, 0.13f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEDIO IZQ. 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.25f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEDIO IZQ.
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.25f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//ANULAR IZQ. 
	model = glm::translate(model, glm::vec3(-0.5f, -0.12f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//ANULAR IZQ.
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//ANULAR IZQ. 
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angAn*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.9f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp2;

	//MEÑIQUE IZQ. 
	model = glm::translate(model, glm::vec3(-0.5f, -0.37f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEÑIQUE IZQ.
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;

	//MEÑIQUE IZQ.
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angMe*0.7f), glm::vec3(0, 1, 0)); 
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 1.0f, 0.3f));
	glDrawArrays(GL_QUADS, 0, 24); //A lonely cube : (
	model = modelTemp;


	glBindVertexArray(0);

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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
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
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += 0.3f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= 0.3f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movY += 0.3f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movY -= 0.3f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.3f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.3f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.3f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.3f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.3f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.3f;

	if (glfwGetKey(window, GLFW_KEY_T)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angHom < 90)
				angHom += 0.2f;
		}
		else {
			if (angHom > -90)
				angHom -= 0.2f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_Y)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angCo < 0)
				angCo += 1.0f;
		}
		else {
			if (angCo > -140)
				angCo -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_U)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMu < 20)
				angMu += 1.0f;
		}
		else {
			if (angMu > -40)
				angMu -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_I)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angPu < 80)
				angPu += 1.0f;
		}
		else {
			if (angPu > 0)
				angPu -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_O)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angIn < 80)
				angIn += 1.0f;
		}
		else {
			if (angIn > 0)
				angIn -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_P)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMed < 80)
				angMed += 1.0f;
		}
		else {
			if (angMed > 0)
				angMed -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_L)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angAn < 80)
				angAn += 1.0f;
		}
		else {
			if (angAn > 0)
				angAn -= 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_K)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMe < 80)
				angMe += 1.0f;
		}
		else {
			if (angMe > 0)
				angMe -= 1.0f;
		}
	}

}



/*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
{
	if (mode == GLFW_MOD_SHIFT) {
		hombro += 2.0f;
	}
	else {
		//lowercase
		hombro -= 2.0f;
	}
}*/

//}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}
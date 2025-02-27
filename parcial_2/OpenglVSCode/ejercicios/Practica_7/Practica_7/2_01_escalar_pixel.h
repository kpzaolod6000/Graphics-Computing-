#pragma once
#include <GL/glew.h>
//#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

using namespace std;


#define numVAOs 1
GLuint renderingProgram; // "Unsigned int" proporcionado por OpenGL (
GLuint vao[numVAOs];

float x = 0.0f;
float inc = 1.0f;

GLuint createShaderProgram() {
	const char* vshaderSource =
		"#version 430 \n" // version 4.3 glsl es parecido a c++
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }"; // posicion de las coordenadas del vertice en el espacio 3D , origen (0,0,0)
// creamos un vertice, no especificamos salida, porque gl_position es por defecto de salida
	const char* fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"// out indica que el variable color es una salida
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER); //generando shader for vertex  vacios
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);//generando shader for fragment vacios


	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	//Luego llama a glShaderSource (), que carga el c�digo GLSL de las cadenas en los objetos de sombreado vac�os.
	//Las dos llamadas especifican el n�mero de l�neas de c�digo en cada sombreador como "1";
	glCompileShader(vShader);
	glCompileShader(fShader);
	//compiladores 
	GLuint vfProgram = glCreateProgram();

	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	//carga el programa que contiene los dos sombreadores compilados en las etapas de la canalizaci�n de OpenGL (�en la GPU!).
	//no ejecuta los sombreadores, solo los carga en el hardware.
	x += inc;
	if (x > 100.0f) inc = -1.0f;
	if (x < 0.0f) inc = 1.0f;
	cout << x << endl;
	glPointSize(x); // un vertice es un pixel, con esto especificamos el tama�o del pixel
	glDrawArrays(GL_POINTS, 0, 1);

}

//
//  main.cpp
//  OpenGL Testing
//
//  Created by Dillon Hammond on 8/4/14.
//  Copyright (c) 2014 Learning. All rights reserved.
//

#define GLEW_STATIC
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include "SOIL.h"
#include "glm.hpp"
#include <iostream>
#include <fstream>
using namespace std;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {
 
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream;
	VertexShaderStream.open(vertex_file_path);
	if(VertexShaderStream.is_open())
	{
		string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
 
	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if(FragmentShaderStream.is_open()){
		string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result;
	// Compile Vertex Shader
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
//	if (Result == GL_TRUE) {
//		cout << "NOOO" << endl;
//		cout << VertexSourcePointer << endl;
//	}

 
	// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
//	if (Result == GL_TRUE) {
//		cout << "NOOO" << endl;
//		cout << FragmentSourcePointer << endl;
//	}

 
	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
 
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
 
	return ProgramID;
}

int main() {
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	glewInit();
	
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	
	GLfloat vertices[] = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLuint shaderProgram = LoadShaders("./Resources/vertexShader.txt", "./Resources/fragmentShader.txt");
	glUseProgram(shaderProgram);
	
	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) {
				break;
			}
		}
		
		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Draw a triangle from the 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		SDL_GL_SwapWindow(window);
	}
	glDeleteProgram(shaderProgram);
	
	glDeleteBuffers(1, &vbo);
	
	glDeleteVertexArrays(1, &vao);
	
	SDL_GL_DeleteContext(context);
    return 0;
}

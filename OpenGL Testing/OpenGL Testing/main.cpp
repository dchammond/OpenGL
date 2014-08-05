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
#define GLM_FORCE_RADIANS
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
using namespace std;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path) {
 
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

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
	ifstream FragmentShaderStream;
	FragmentShaderStream.open(fragment_file_path);
	if(FragmentShaderStream.is_open()){
		string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	
	// Read the Geometry Shader code from the file
	string GeometryShaderCode;
	ifstream GeometryShaderStream;
	GeometryShaderStream.open(geometry_file_path);
	if(GeometryShaderStream.is_open()){
		string Line = "";
		while(getline(GeometryShaderStream, Line))
			GeometryShaderCode += "\n" + Line;
		GeometryShaderStream.close();
	}
	
	GLint Result;
	// Compile Vertex Shader
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		cout << "NOOOV" << endl;
	}

 
	// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		cout << "NOOOF" << endl;
	}
	
	// Compile Geometry Shader
	char const * GeometrySourcePointer = GeometryShaderCode.c_str();
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer , NULL);
	glCompileShader(GeometryShaderID);
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		cout << "NOOOG" << endl;
	}

	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
	glLinkProgram(ProgramID);
 
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteShader(GeometryShaderID);
 
	return ProgramID;
}

int main() {
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	
	GLuint shaderProgram = LoadShaders("./Resources/vertexShader.txt", "./Resources/fragmentShader.txt", "./Resources/geometryShader.txt");
	glUseProgram(shaderProgram);
	
	// Create VBO with point coordinates
	GLuint vbo;
	glGenBuffers(1, &vbo);
	
	GLfloat points[] = {
		-0.45f,  0.45f,
		0.45f,  0.45f,
		0.45f, -0.45f,
		-0.45f, -0.45f,
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Specify layout of point data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) {
				break;
			}
		}
		
		// Render frame
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_POINTS, 0, 4);
		
		SDL_GL_SwapWindow(window);
	}
	
	glDeleteProgram(shaderProgram);
	
	glDeleteBuffers(1, &vbo);
	
	SDL_GL_DeleteContext(context);
    return 0;
}

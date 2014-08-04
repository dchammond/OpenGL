//
//  main.cpp
//  OpenGL Testing
//
//  Created by Dillon Hammond on 8/4/14.
//  Copyright (c) 2014 Learning. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

int main() {
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}
		
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
    return 0;
}

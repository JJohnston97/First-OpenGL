/// \File Main.cpp
/// \breif Holds all main information for the game, as well as cotaining the Game Loop

//System Includes
#include <iostream>			//Include Iostream to write to console 
#include <string>			//Include String for the use of strings
//Library Includes 
#include <SDL/SDL.h>		//includes SDL2 for keyboard and mouse inputs, as well as graphics window
#include <SDL_mixer.h>		//includes SDL mixer for sound
//Project Includes
#include "GameObject.h"		//Includes GameObject.h anything that is in game object
#include "glew.h"			//Includes Glew to use features of glew such a glm
#include "ParticleSystem.h"	//Include PaticleSystem, to implement one 
#include "Scene.h"			//Inlcudes Scene.h for gameobjects information


bool InitGL()
{
	glewExperimental = GL_TRUE;	//Way around glew having a problem with Core Opengl

	GLenum err = glewInit();
	if ( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}


int main(int argc, char *argv[])
{
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);		//Initilise SLD Audio used for sound clips

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )				
	{
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;	//Error message output if SDL cannot load
		return -1;																					//Close the window
	}

	if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )		//Initilise 
		std::cout << "ERROR : " << Mix_GetError() << std::endl;		//Set up for any errors from mixer

	Mix_Chunk *Short = Mix_LoadWAV("Moo.wav");						//Creates a clip called Short containing wav called Moo

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);			//Setting Up Version 4 main of OpenGl
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);			//Setting Up Version 4.3 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //Using the latest versions of the deprecated functions

	int winPosX = 100;		//Creating window parameters
	int winPosY = 100;		//Creating window Parameters
	int winWidth = 800;		//Creating window Parameters
	int winHeight = 800;	//Creating window Parameters

	SDL_Window *window = SDL_CreateWindow("My Window!!!",  //The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0); //Tells SDL what window to use
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);		 //Allows you to use OpenGL to draw to the window

	if ( !InitGL() )
	{
		return -1; //Call initialisation function to set up GLEW and print out some GL info to console
	}

	unsigned int lastTime = SDL_GetTicks(); //Work out how much time has passed frame to frame

	glEnable(GL_DEPTH_TEST);	           //This is enables to make sure triangles are always draw in the correct order

	Scene myScene;                         //The scene contains all the objects etc

	bool cmdRotateLeft = false, cmdRotateRight = false, cmdRotateUp = false, cmdRotateDown = false;										  //Used to rotate the camera
	bool cmdRollLeft = false, cmdRollRight = false, cmdPitchUp = false, cmdPitchDown = false, cmdThrustUp = false, cmdThrustDown = false; //Used to roll the camera

	Player *mainPlayer = myScene.getPlayer();

	bool go = true;
	while (go)		//Start of the Main game Loop
	{
		SDL_Event incomingEvent;              //Create an SDL event for any sdl event type when used, mouse or keyboard input etc
		while (SDL_PollEvent(&incomingEvent)) //Used to check if an event is queued
		{
			switch (incomingEvent.type)		  //Switch based on the event type coming in
			{
			case SDL_QUIT:
				go = false;					  //If the window is closed or a reason to exit this will be set to false ending the game loop
				break;
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym) //Incoming Keyboard event
				{
				case SDLK_DOWN:
				{
					cmdRotateDown = true;			  //Down Arrow
					break;
				}
				case SDLK_UP:
				{
					cmdRotateUp = true;				  //Up Arrow
					break;
				}
				case SDLK_LEFT:
				{
					cmdRotateLeft = true;			  //Left Arrow
					break;
				}
				case SDLK_RIGHT:
				{
					cmdRotateRight = true;			  //Right Arrow
					break;
				}
				case SDLK_a:
				{
					cmdRollLeft = true;				  //A Key
					break;
				}
				case SDLK_d:
				{
					cmdRollRight = true;			  //D Key
					break;
				}
				case SDLK_w:
					cmdPitchUp = true;				  //W Key
					break;
				case SDLK_s:
				{
					cmdPitchDown = true;			  //S Key
					break;
				}
				case SDLK_LSHIFT:
				{
					Mix_PlayChannel(-1, Short, 0);	  //Plays the music clip when the left shift is pressed
					cmdThrustUp = true;				  //Left Shift
					break;
				}
				case SDLK_LCTRL:
				{
					cmdThrustDown = true;			  //Left CTRL
					break;
				}
				case SDLK_SPACE:					  //Space Bar
					break;
				}
				break;

			case SDL_KEYUP:	//Event on the Key Up
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_DOWN:
				{
					cmdRotateDown = false;			  //Down Arrow
					break;
				}
				case SDLK_UP:
				{
					cmdRotateUp = false;			  //Up Arrow
					break;
				}
				case SDLK_LEFT:
				{
					cmdRotateLeft = false;			  //Left Arrow
					break;
				}
				case SDLK_RIGHT:
				{
					cmdRotateRight = false;			  //Right Arrow
					break;
				}
				case SDLK_a:
				{
					cmdRollLeft = false;			  //A key
					break;
				}
				case SDLK_d:
				{
					cmdRollRight = false;			  //D key
					break;
				}
				case SDLK_w:
				{
					cmdPitchUp = false;			      //W key
					break;
				}
				case SDLK_s:
				{
					cmdPitchDown = false;			  //S Key
					break;
				}
				case SDLK_LSHIFT: 
				{
					cmdThrustUp = false;			  //Left Shift
					break;
				}
				case SDLK_LCTRL:
				{
					cmdThrustDown = false;			  //Left Control
					break;
				}
				}
				break;
			}
		}

		unsigned int current = SDL_GetTicks();	                //Current is set to the time between frames
	
		float deltaTs = (float)(current - lastTime) / 1000.0f;	//Change in time from last frame to current frame
		lastTime = current;                                     //Last time is equal to current

		
		if ( cmdRotateLeft & !cmdRotateRight )
		{
			myScene.ChangeCameraAngleY(1.0f * deltaTs);         //Control the camera based on our input commands, left and right
		}
		else if ( cmdRotateRight & !cmdRotateLeft )
		{
			myScene.ChangeCameraAngleY(-1.0f * deltaTs);        //Control the camera based on our input commands, right and left
		}

		if ( cmdRotateUp & !cmdRotateDown )
		{
			myScene.ChangeCameraAngleX(1.0f * deltaTs);         //Control the camera based on our input commands, rotate up and now down
		}
		else if ( cmdRotateDown & !cmdRotateUp )
		{
			myScene.ChangeCameraAngleX(-1.0f * deltaTs);
		}


		if ( cmdRollLeft & !cmdRollRight )
		{
			mainPlayer->ChangeRoll(-1.0f);
		}
		else if ( cmdRollRight & !cmdRollLeft )
		{
			mainPlayer->ChangeRoll(1.0f);
		}
		else
		{
			mainPlayer->ChangeRoll(0.0f);
		}

		if ( cmdPitchUp & !cmdPitchDown )
		{
			mainPlayer->ChangePitch(1.0f);
		}
		else if ( cmdPitchDown & !cmdPitchUp )
		{
			mainPlayer->ChangePitch(-1.0f);
		}
		else
		{
			mainPlayer->ChangePitch(0.0f);
		}

		if ( cmdThrustUp & !cmdThrustDown )
		{
			mainPlayer->ChangeThrust(1.0f*deltaTs);
		}
		else if ( cmdThrustDown & !cmdThrustUp )
		{
			mainPlayer->ChangeThrust(-1.0f*deltaTs);
		}

		
		myScene.Update(deltaTs);		//Update the scene
		glClearColor(0.275f, 0.510f, 0.706f, 0.0f); //Specify the colour to clear the framebuffer to
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myScene.Draw();					//Draw the scene
		SDL_GL_SwapWindow(window);

		if ( deltaTs < (1.0f / 50.0f) )
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}
	
	}

	Mix_FreeChunk(Short);		//Frees the clip data


	Short = nullptr;			//Sets the clip to a NUllprt
	
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	Mix_Quit();					//Quit the mixer for audio	
	SDL_Quit();					//Quits SDL

	return 0;
}

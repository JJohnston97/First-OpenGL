/// \File Material.cpp
/// \Breif Handles any material / textures 

//System Includes
#include <iostream>				//Include for writing to console
#include <fstream>				//Include Fstream
//Library Includes
#include <SDL/SDL.h>			//Include SDL2
#include <GLM/gtc/type_ptr.hpp>	//Include Glew
#include <GLM/gtc/matrix_transform.hpp>	
//Project Includes
#include "Material.h"		//Include Material.h

Material::Material()
{

	m_texture1 = 0;			//Sets Texture1 to 0
	m_texture2 = 0;			//Sets Texture2 to 0

	objectShader = new Shader("FragShader.txt", "VertShader.txt");	//Sets the shaders
}

Material::~Material()
{
	
}



unsigned int Material::LoadTexture(std::string filename)
{

	SDL_Surface *image = SDL_LoadBMP(filename.c_str());	//Load an SDL Surface

	if ( !image )                                         //Check it worked
	{
		std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;   //Output Error if cannot load bmp
		return 0;
	}

	unsigned int texName = 0;			//Create OpenGL Texture
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //openGl mag Filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //Telling OpenGl to use linear or generate a mipmap
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels); //SDL loads images in BGR order

	SDL_FreeSurface(image);		//Free SDL image

	return texName;
}




void Material::setMatrices(glm::mat4 &modelMatrix, glm::mat4 &invModelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{

	objectShader->setMatrices(modelMatrix, invModelMatrix, viewMatrix, projMatrix);   //Sets The Martrices to the Object 
}


void Material::Apply()
{

	objectShader->Add();

	glUseProgram(_shaderProgram);		//Setting Up texture 1
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(objectShader->m_shaderTex1SamplerLocation, 0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);

	if ( m_texture2 != 0 )
	{
		glActiveTexture(GL_TEXTURE1);	//Setting up Texture 2
		glUniform1i(objectShader->m_shaderTex2SamplerLocation, 1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);
	}
}

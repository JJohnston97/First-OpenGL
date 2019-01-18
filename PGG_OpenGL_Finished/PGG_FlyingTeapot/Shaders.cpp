/// \File Shader.cpp
/// \Breif Handles anything to do with shaders

//System Includes
#include <fstream>
#include <iostream>
//Library Includes
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <SDL/SDL.h>
//Project Includes
#include "Shaders.h"



Shader::Shader(std::string _FragShader, std::string _VertShader)
{
	// Initialise everything here
	m_shaderModelMatLocation = 0;
	m_shaderViewMatLocation = 0;
	m_shaderProjMatLocation = 0;

	m_shaderDiffuseColLocation = 0;
	_shaderEmissiveColLocation = 0;
	m_shaderWSLightPosLocation = 0;
	_shaderSpecularColLocation = 0;

}

Shader::~Shader()
{
}

bool Shader::LoadShaders(std::string vertFilename, std::string fragFilename)
{
	// OpenGL doesn't provide any functions for loading shaders from file


	std::ifstream vertFile(vertFilename);
	char *vShaderText = NULL;

	if ( vertFile.is_open() )
	{
		// Find out how many characters are in the file
		vertFile.seekg(0, vertFile.end);
		int length = (int)vertFile.tellg();
		vertFile.seekg(0, vertFile.beg);

		// Create our buffer
		vShaderText = new char[length + 1];

		// Transfer data from file to buffer
		vertFile.read(vShaderText, length);

		// Check it reached the end of the file
		if ( !vertFile.eof() )
		{
			vertFile.close();
			std::cerr << "WARNING: could not read vertex shader from file: " << vertFilename << std::endl;
			return false;
		}

		// Find out how many characters were actually read
		length = (int)vertFile.gcount();

		// Needs to be NULL-terminated
		vShaderText[length] = 0;

		vertFile.close();
	}
	else
	{
		std::cerr << "WARNING: could not open vertex shader from file: " << vertFilename << std::endl;
		return false;
	}


	std::ifstream fragFile(fragFilename);
	char *fShaderText = NULL;

	if ( fragFile.is_open() )
	{
		// Find out how many characters are in the file
		fragFile.seekg(0, fragFile.end);
		int length = (int)fragFile.tellg();
		fragFile.seekg(0, fragFile.beg);

		// Create our buffer
		fShaderText = new char[length + 1];

		// Transfer data from file to buffer
		fragFile.read(fShaderText, length);

		// Check it reached the end of the file
		if ( !fragFile.eof() )
		{
			fragFile.close();
			std::cerr << "WARNING: could not read fragment shader from file: " << fragFilename << std::endl;
			return false;
		}

		// Find out how many characters were actually read
		length = (int)fragFile.gcount();

		// Needs to be NULL-terminated
		fShaderText[length] = 0;

		fragFile.close();
	}
	else
	{
		std::cerr << "WARNING: could not open fragment shader from file: " << fragFilename << std::endl;
		return false;
	}



	// The 'program' stores the shaders
	m_shaderProgram = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	// Give GL the source for it
	glShaderSource(vShader, 1, &vShaderText, NULL);
	// Delete buffer
	delete[] vShaderText;
	// Compile the shader
	glCompileShader(vShader);
	// Check it compiled and give useful output if it didn't work!
	if ( !CheckShaderCompiled(vShader) )
	{
		std::cerr << "ERROR: failed to compile vertex shader" << std::endl;
		return false;
	}
	// This links the shader to the program
	glAttachShader(m_shaderProgram, vShader);

	// Same for the fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	// Delete buffer
	delete[] fShaderText;
	glCompileShader(fShader);
	if ( !CheckShaderCompiled(fShader) )
	{
		std::cerr << "ERROR: failed to compile fragment shader" << std::endl;
		return false;
	}
	glAttachShader(m_shaderProgram, fShader);

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram(m_shaderProgram);
	// Check this worked
	GLint linked;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linked);
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(m_shaderProgram, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return false;
	}


	// We will define matrices which we will send to the shader
	// To do this we need to retrieve the locations of the shader's matrix uniform variables
	glUseProgram(m_shaderProgram);
	m_shaderModelMatLocation = glGetUniformLocation(m_shaderProgram, "modelMat");
	m_shaderInvModelMatLocation = glGetUniformLocation(m_shaderProgram, "invModelMat");
	m_shaderViewMatLocation = glGetUniformLocation(m_shaderProgram, "viewMat");
	m_shaderProjMatLocation = glGetUniformLocation(m_shaderProgram, "projMat");

	m_shaderDiffuseColLocation = glGetUniformLocation(m_shaderProgram, "diffuseColour");
	_shaderEmissiveColLocation = glGetUniformLocation(m_shaderProgram, "emissiveColour");
	_shaderSpecularColLocation = glGetUniformLocation(m_shaderProgram, "specularColour");
	m_shaderWSLightPosLocation = glGetUniformLocation(m_shaderProgram, "worldSpaceLightPos");

	m_shaderTex1SamplerLocation = glGetUniformLocation(m_shaderProgram, "tex1");
	m_shaderTex2SamplerLocation = glGetUniformLocation(m_shaderProgram, "tex2");

	return true;
}

void Shader::setMatrices(glm::mat4 & modelMatrix, glm::mat4 & invModelMatrix, glm::mat4 & viewMatrix, glm::mat4 & projMatrix)
{
	glUseProgram(m_shaderProgram);
	// Send matrices and uniforms
	glUniformMatrix4fv(m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(m_shaderInvModelMatLocation, 1, GL_TRUE, glm::value_ptr(invModelMatrix));
	glUniformMatrix4fv(m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));
}

bool Shader::CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}

void Shader::Add()
{

	glUseProgram(m_shaderProgram);
	glUniform4fv(m_shaderWSLightPosLocation, 1, glm::value_ptr(m_lightPosition));

	glUniform3fv(_shaderEmissiveColLocation, 1, glm::value_ptr(m_emissiveColour));
	glUniform3fv(m_shaderDiffuseColLocation, 1, glm::value_ptr(m_diffuseColour));
	glUniform3fv(_shaderSpecularColLocation, 1, glm::value_ptr(m_specularColour));
}

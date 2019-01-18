/// \file Material.h
/// \brief Used for textures and materials on objects

#ifndef __MATERIAL__H_
#define __MATERIAL__H_


//File Includes
//System Includes
#include <string>
//Libary Includes
#include <GLM/glm.hpp>
//Porject Includes
#include "glew.h"
#include "Shaders.h"


//Header Content

class Material
{
public:
	Material();    //Constructor
	~Material();   //Destructor

	void setMatrices(glm::mat4 &modelMatrix, glm::mat4 &invModelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projMatrix); //Creates the standard matrices needed for the shader
	void setEmissiveColour( glm::vec3 input ) { objectShader->m_emissiveColour = input;}	//Emissive Material Colour
	void setDiffuseColour( glm::vec3 input ) { objectShader->m_diffuseColour = input;}	//Diffuse Material Colour
	void setSpecularColour( glm::vec3 input ) { objectShader->m_specularColour = input;}	//Specular Material Colour
	void setLightPosition( glm::vec3 input ) { objectShader->m_lightPosition = input;}   //Set Light position in world space
	void Apply();																		//Applies the shaders
	Shader* getShader(){ return objectShader; }							                //Shader pointer to Get shader function

	bool setTexture( std::string filename ) {m_texture1 = LoadTexture(filename); return m_texture1>0;}	//Applies first texture including, Ambient, Diffuse and Specular
	bool setTexture2(std::string filename) { m_texture2 = LoadTexture(filename); return m_texture2>0; }	//Appplies second texture for Multi - Texturing

	
protected:

	Shader* objectShader;	//Initialise Shader Pointer variable
	
	int _shaderProgram;		//Initialise ShaderProgram variable
	
	unsigned int LoadTexture( std::string filename );	//Used to load a .BMP flie
	unsigned int m_texture1;								//Initialise Texture 1
	unsigned int m_texture2;								//Initialise Texture 2
	


};




#endif //_MATERIAL_H

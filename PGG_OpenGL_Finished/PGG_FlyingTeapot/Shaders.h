/// \File Shader.H
/// \Breif Handles anything to do with the shaders

#ifndef _SHADER_H_
#define _SHADER_H_

//File Includes
//System Includes
#include <string>		//Includes String
//Libary Includes
#include <GLM/glm.hpp>	//Include GLM
//Project Includes
#include "glew.h"		//Include Glew.h

//Header Contents
class Shader
{
public:
	Shader(std::string _FragShader, std::string _VertShader);  //Constructor
	~Shader();												   ////Destructor


	bool CheckShaderCompiled(GLint shader);	                               //Bool to check the shaders compiled
	bool LoadShaders(std::string vertFilename, std::string fragFilename);  //Bool to load Shaders
	void setMatrices(glm::mat4 &modelMatrix, glm::mat4 &invModelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projMatrix); //Set matrices for materials, to send down the pipeline
	void SetEmissiveColour(glm::vec3 input) { m_emissiveColour = input; }  //Set Emissive Colour function
	void SetDiffuseColour(glm::vec3 input) { m_diffuseColour = input; }	  //Set Diffuse Colour Function
	void SetSpecularColour(glm::vec3 input) { m_specularColour = input; }  //Set Specular Colour Function
	void SetLightPosition(glm::vec3 input) { m_lightPosition = input; }	  //Set Light Position Function
	void Add();                                                           //New function for shader management

	int m_shaderProgram;	//The OpenGL Shader program handle

	//Locations of Uniforms in the vertex shader
	int m_shaderModelMatLocation;
	int m_shaderInvModelMatLocation;
	int m_shaderViewMatLocation;
	int m_shaderProjMatLocation;

	// Location of Uniforms in the fragment shader
	int m_shaderDiffuseColLocation, _shaderEmissiveColLocation, _shaderSpecularColLocation;
	int m_shaderWSLightPosLocation;
	int m_shaderTex1SamplerLocation;
	int m_shaderTex2SamplerLocation;

	//Local store of material properties to be sent to the shader
	glm::vec3 m_emissiveColour, m_diffuseColour, m_specularColour;			//Vec3 for colours
	glm::vec3 m_lightPosition;											//Vec3 for light position

private:

};

#endif //_SHADER_H
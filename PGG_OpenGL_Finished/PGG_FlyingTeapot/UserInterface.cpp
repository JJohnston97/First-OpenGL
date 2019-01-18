/// \File UserInterface.cpp
/// \Breif Handles any orthographic objects used for User Interface

//Libary Includes
#include <GLM/gtc/type_ptr.hpp>				//Include Glew
#include <GLM/gtc/matrix_transform.hpp>
//Project Includes
#include "UserInterface.h"					//Include UserInterface.h


UI::UI()
{
	m_UImesh = NULL;					//Mesh initialised as NULL				
	m_UImaterial = NULL;				//Material Initalised as NULL
	m_scale = glm::vec3(1, 1, 1);	//Standard scale 1, 1, 1


}


UI::~UI()
{


}

void UI::Update(float deltaTs)
{
	while (m_rotation.y > (3.14159265358979323846 * 2.0))
	{
		m_rotation.y -= (float)(3.14159265358979323846 * 2.0);
	}

	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);							//Setting the translate of the gameObject
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0, 1, 0));			//Matrices are not changed elsewhere so can be used in update
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);									//Including scale
	m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -m_rotation.y, glm::vec3(0, 1, 0));


}

void UI::DrawOrtho(glm::mat4 &viewMatrix, glm::mat4 &projMatrixOrtho)
{
	if ( m_UImesh != NULL )				//If the mesh is not equal to NULL (A mesh has been given)
	{
		if ( m_UImaterial != NULL )		//And the material is not equal to NULL (A material has been given)
		{
			m_UImaterial->setMatrices(m_modelMatrix, m_invModelMatrix, viewMatrix, projMatrixOrtho);	//Give all matrices to the material, and send them to the shader
			m_UImaterial->Apply();																	//Send the material to the shader, this activates the shader
		}																							//Drawn in orthographic view
		m_UImesh->Draw(); //Send info down the pipeline
	
	}

}
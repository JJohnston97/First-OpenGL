/// \File GameObject.cpp
/// \Breif Used for creating and handling gameobjects update and draw

//Library Includes
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
//Project Includes
#include "GameObject.h"				//Include GameObject.h

GameObject::GameObject()
{
	
	m_mesh = NULL;					//Mesh initialised as NULL
	m_material = NULL;				//Material Initalised as NULL
	m_scale = glm::vec3(1, 1, 1);	//Standard scale 1, 1, 1
	destroy = false;				//Destory set to false until collision
}

GameObject::~GameObject()
{
	
}

void GameObject::Update(float deltaTs)
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

void GameObject::Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	if ( m_mesh != NULL )		    //If the mesh is not equal to NULL (A mesh has been given)
	{
		if ( m_material != NULL )	//And the material is not equal to NULL (A material has been given)
		{
			m_material->setMatrices(m_modelMatrix, m_invModelMatrix, viewMatrix, projMatrix);	//Give all matrices to the material, and send them to the shader
			m_material->Apply();																//Send the material to the shader, this activates the shader
			
		}
		
		m_mesh->Draw(); //Send the Mesh data down the pipeline

	}
}




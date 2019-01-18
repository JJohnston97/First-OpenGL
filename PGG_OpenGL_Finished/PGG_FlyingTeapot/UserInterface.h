/// \File UserInterface.h
/// \brief handles user interface seperate from game objects

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_


//File Includes
//Project Includes
#include "GameObject.h" //Include GameObject.h
#include "Mesh.h"		//Include Mesh.h
#include "Material.h"	//Include Material.h

//Header Contents

class UI : public GameObject		//UI inherits from GameObject
{
public:
	UI();		//Constructor
	~UI();		//Destructor

	void setUIMesh(Mesh *input) { m_UImesh = input; }																			//Sets the UI Mesh
	void setUIMaterial(Material *input) { m_UImaterial = input; }																//Adds the UI Material to that mesh
	void setUIPosition( float posX, float posY, float posZ ) { m_position.x = posX; m_position.y = posY; m_position.z = posZ; }	//Sets the UI Position
	void setUIPosition(glm::vec3 value) { m_position = value; }																	//objects in the scene
	void setUIScale(float scaleX, float scaleY, float scaleZ) { m_scale.x = scaleX; m_scale.y = scaleY; m_scale.z = scaleZ; }	//Sets Scale of the UI

	virtual void Update(float deltaTs);												//Updates all UI objects
	virtual void DrawOrtho(glm::mat4 &viewMatrix, glm::mat4 &projMatrixOrtho);		//Draw funtion, drawn in Orthographic for UI

protected:

	Mesh *m_UImesh;				//UI mesh
	Material *m_UImaterial;		//UI Material

	glm::mat4 m_modelMatrix;	//Mat 4 Model Matrix 
	glm::mat4 m_invModelMatrix; //Mat 4 inverse Model Matrix 
	glm::vec3 m_position;		//Vec3 for positio
	glm::vec3 m_scale;			//Vec3 for Scale
	glm::vec3 m_rotation;		//Vec3 for Rotation


};

#endif // _USER_INTERFACE_H_

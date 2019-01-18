/// \file GameObject.h
/// \brief handles game object creation for my collectables

#ifndef __MILK__H_
#define __MILK__H_


//File Includes
//Project Includes
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

//Header Contents

class Milk : public GameObject		//Milk inherits from GameObject
{
public:

	Milk();    //Constructor
	~Milk();   //Destructor

	void Update(float deltaTs);								//Update Function called every frame
	void Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);//Draw Function used to send the data down the pipeline to be drawn
	
	Milk *_Object1;				            //First Milk Object
	Milk *_secondObject;		            //Second Milk Object

	glm::vec3 getScale() { return m_scale; }	//Vec3 Get scale function used for Collision


protected:

	Mesh *_mesh;		       	//Model Gemoetry

	Material *m_material;        //The material contains the shader
	Material *m_material2;

	glm::mat4 m_modelMatrix;     //Materix for the position and orientation of the game object
	glm::mat4 m_invModelMatrix;
	glm::vec3 m_position;		//Position of the model, the rotation and model matix must be built from this as well
	glm::vec3 m_rotation;		//Rotation for controlling the orientation of the model
	glm::vec3 m_scale;			//Scale for scaling the game objects


};



#endif //_MILK_H_

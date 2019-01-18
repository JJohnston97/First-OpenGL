/// \file GameObject.h
/// \brief handles game object creation as well as get and sets for game objects

#ifndef __GAME_OBJECT__H_
#define __GAME_OBJECT__H_


//File Includes

//Porject Includes
#include "Mesh.h"
#include "Material.h"

//Header Contents

class GameObject
{
public:

	GameObject();		//Constructor
	~GameObject();		//Destructor

	void setMesh(Mesh *input) {m_mesh = input;}					//Set mesh function used to assign OBJ files to mesh
	void setMaterial(Material *input) {m_material = input;}		//Set material function used to apply a texture to that model
	void setMaterial2(Material *input) {m_material2 = input; }	//Set material function used to apply a texture to that model

	void setPosition( float posX, float posY, float posZ ) {m_position.x = posX; m_position.y = posY; m_position.z = posZ;}	//Set position function used to set position of the player and any
	void setPosition( glm::vec3 value) {m_position = value;}																	//objects in the scene
	void setRotation( float rotX, float rotY, float rotZ ) {m_rotation.x = rotX; m_rotation.y = rotY; m_rotation.z = rotZ;}	//Set roation allows for rotation of a game object
	void setScale(float scaleX, float scaleY, float scaleZ) { m_scale.x = scaleX; m_scale.y = scaleY; m_scale.z = scaleZ; }	//Set scale allows for the scaling of a game object
	void setDestroy(bool destroy) { this->destroy = destroy; };
	
	bool isDestroyed() { return destroy; }
	
	glm::vec3 getPosition() {return m_position;}						   //Get function for position to provide an X,Y,Z for a game object
	glm::vec3 getScale() { return m_scale; }
	
	virtual void Update( float deltaTs );							   //Update function set as virtual as it will be redefined in derived classes
	virtual void Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);   //Draw function that will take a camera orientation and projection


protected:

	bool destroy;				//Bool used to destroy objects once a collision has happened
	
	Mesh *m_mesh;		       	//Model Gemoetry

	Material *m_material;        //The material contains the shader
	Material *m_material2;
	
	glm::mat4 m_modelMatrix;     //Materix for the position and orientation of the game object
	glm::mat4 m_invModelMatrix;		
	glm::vec3 m_position;		//Position of the model, the rotation and model matix must be built from this as well
	glm::vec3 m_rotation;		//Rotation for controlling the orientation of the model
	glm::vec3 m_scale;			//Scale for scaling the game objects


};



#endif // _GAME_OBJECT_H_

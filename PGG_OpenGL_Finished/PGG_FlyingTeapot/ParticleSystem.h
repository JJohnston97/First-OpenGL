/// \file Particle System.h
/// \brief handles variables and set up for a particle system. This particle system was an attempt as I was using a java example that I was trying to mold into a c++ file


// This particle system was an attempt as I was using a java example that I was trying to mold into a c++ file. The example was creating a particle system in a far to object orientated way 
// and I could not fiure out how to make it work. So, this was left as an attempt for you to see (Referances for this can be found in my report) 

#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

//File Includes
//System Includes
#include <string>						//Allows for the use of strings
//Project Includes
#include <GLM/glm.hpp>					//This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> //This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp>			//This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>

//Header Contents
class Particle {

public:

	Particle(float pps, float speed, float gravityComplient, float lifeLength);  //Constructor
	~Particle();																 //Destructor


	glm::vec3 m_Position;		//New vec3 for position
	glm::vec3 m_Velocity;		//New vec3 for velocity
	glm::vec3 m_Rotation;		//New vec3 for Rotation
	float m_Scale;			    //New vec3 for Scale
	float m_pps;				//Particle Per Square
	float m_speed;				//Speed they are travelling
	float m_gravityComplient;	//Gravity to make them fall
	float m_lifeLength;			//How long they will stick around for
	float m_timeParticleIsAlive;//How long its been alive
	float m_ParticlesToCreate;  //Particles Left to create
	float m_particalToDraw;		//Particles left to draw
	float m_count;              //Count of how many there are
	int m_Random;               //Random int 1
	int m_Random2;				//Random int 2
	float m_dirX;				//X direction
	float m_dirZ;				//z direction

	Particle *_ParticleToDraw;			//Create a new point to a particle

	glm::vec3 setPosition() { return m_Position; }		//Return the position
	glm::vec3 setRotation() { return m_Rotation; }		//Return the Rotation 													
	glm::vec3 getPosition() { return m_Position; }		//Gets Position											
	glm::vec3 getRotation() { return m_Rotation; }		//Gets Rotation

	bool Update(float deltaTs);						//Update Function
	void Draw();									//Draw function
	void generateParticles(float deltaTs);			//Generate Particles function


	glm::mat4 m_viewMatrix;				//View matrix 
	glm::mat4 m_projMatrix;				//projecttion matrix
	glm::mat4 m_ortho;					//Orthographic view
	float m_cameraAngleX, m_cameraAngleY;	//Camera position
	glm::vec3 m_lightPosition;			//Light position impact on player
	glm::quat m_cameraOrientation;		//Camera position x,y,z

};


#endif // _PARTICLE_SYSTEM_H_
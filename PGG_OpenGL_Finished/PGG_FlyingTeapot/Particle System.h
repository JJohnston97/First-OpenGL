/// \file Particle System.h
/// \brief handles variables and set up for a particle system
#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>

#include <string>




class Particle {

public:
	
	Particle(float pps, float speed, float gravityComplient, float lifeLength);
	~Particle();

	
	glm::vec3 _Position;		//New vec3 for position
	glm::vec3 _Velocity;		//New vec3 for velocity
	glm::vec3 _Rotation;		//New vec3 for Rotation
	float Scale;			//new vec3 for Scale
	float pps;					//Particle Per Square
	float speed;				//speed they are travelling
	float gravityComplient;		//gravity to make them fall
	float lifeLength;			//How long they will stick around for
	float timeParticleIsAlive;  //How long its been alive
	float ParticlesToCreate;
	float particalToDraw;
	float count;
	int Random;
	int Random2;
	float dirX;
	float dirZ;

	Particle *_ParticleToDraw;			//Create a new point to a particle
	
	glm::vec3 SetPosition() { return _Position; }		//Return the position
	glm::vec3 SetRotation() { return _Rotation; }		//Return the Rotation 
	//glm::vec3 SetScale() { return _Scale; }			//Return the Scale

	glm::vec3 GetPosition() { return _Position; }		//Gets Position
	//glm::vec3 GetScale() { return _Scale; }			//Gets Scale
	glm::vec3 GetRotation() { return _Rotation; }		//Gets Rotation

	bool Update(float deltaTs);						//Update Function
	void Draw();									//Draw function
	void generateParticles(float deltaTs);			//Generate Particles function


	glm::mat4 _viewMatrix;				//View matrix 
	glm::mat4 _projMatrix;				//projecttion matrix
	glm::mat4 _ortho;					//Orthographic view
	float _cameraAngleX, _cameraAngleY;	//Camera position
	glm::vec3 _lightPosition;			//Light position impact on player
	glm::quat _cameraOrientation;		//Camera position x,y,z
	
};


#endif // _PARTICLE_SYSTEM_H_
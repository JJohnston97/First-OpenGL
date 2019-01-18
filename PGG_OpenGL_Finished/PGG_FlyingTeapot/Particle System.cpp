#include <iostream>
#include "Particle System.h"
#include <GLM/glm.hpp>						//This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp>		//This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp>				//This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>
#include <string>*/
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>

Particle::Particle(float pps, float speed, float gravityComplient, float lifeLength)
{
	//_Position = _Position;  //not sure whats needed as in referance to returns

	srand(time(NULL));

	Random = rand() % 10 + 1;
	Random2 = rand() % 20 + 1;
	gravityComplient = -50;
	_cameraAngleX = 0.3f, _cameraAngleY = 1.5f;
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);         //Set up a projection matrix
	_lightPosition = glm::vec3(-50, -50, -100);							 //Position of the light, in world-space
	
	_ParticleToDraw = new Particle(0,0,0,0);

}


Particle::~Particle()												//Destructor function is being called to destory a sprite
{
		
}

bool Particle::Update(float deltaTs)
{
	_Velocity.y += gravityComplient * timeParticleIsAlive;		//Veclocity of the Y is equaly to the weight of 50 x by the time its been alive (longer its alive the lower it gets)
	glm::vec3 Change = _Velocity;								//How much the particle position should change baised on velocity, in one second
	Change *= deltaTs;			
	_Position += Change;
	timeParticleIsAlive += deltaTs;
	
	if (timeParticleIsAlive < lifeLength)
	{
		return true;
	}

	return false;
}


void Particle::generateParticles(float deltaTs)
{
	ParticlesToCreate = pps * deltaTs;
	count = (int)floor(ParticlesToCreate);
	particalToDraw = ParticlesToCreate + Random;

	for (size_t i = 0; i < count; ++i)
	{
		_ParticleToDraw->Draw();

	}

	if (Random < particalToDraw)
	{
		_ParticleToDraw->Draw();

	}


}

void Particle::Draw()
{
	std::vector <Particle*> ParticleSystem;

	ParticleSystem.push_back(_ParticleToDraw);

	for each (Particle* P in ParticleSystem)
	{

	dirX = (float) Random * 2.0f - 1.0f;
	dirZ = (float) Random2 * 2.0f - 1.0f;
	_Velocity = { dirX, 1, dirZ };
	glm::normalize(_Velocity);
	Scale = speed;


	}
	
}

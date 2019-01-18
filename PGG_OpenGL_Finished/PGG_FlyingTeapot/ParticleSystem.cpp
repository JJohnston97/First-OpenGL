/// \File ParticleSystem.cpp
/// \Brief Foundation for a particle system

//System Includes
#include <algorithm>						//Include algorithm
#include <iostream>							//Write to comand window for dbugs
#include <math.h>							//Include math.h
#include <string>							//Include for use for string
#include <time.h>							//Include Time.h for srand
#include <vector>							//Include for the use for vector
//Library Includes
#include <GLM/glm.hpp>						//This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp>		//This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp>				//This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>
//Project Include
#include "ParticleSystem.h"					//Include ParticleSystem.h

Particle::Particle(float pps, float speed, float gravityComplient, float lifeLength)
{
	//_Position = _Position;  //not sure whats needed as in referance to returns

	srand(time(NULL));

	m_Random = rand() % 10 + 1;											  //Creates a random number between 1-10
	m_Random2 = rand() % 20 + 1;											  //Creates a random number between 20 - 1
	gravityComplient = -50;												  //Gravity is set to -50
	m_cameraAngleX = 0.3f, m_cameraAngleY = 1.5f;					
	m_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);          //Set up a projection matrix
	m_lightPosition = glm::vec3(-50, -50, -100);							  //Position of the light, in world-space

	_ParticleToDraw = new Particle(0, 0, 0, 0);							  //Setting the partcle to draw to a new particle

}


Particle::~Particle()												//Destructor function is being called to destory a sprite
{

}

bool Particle::Update(float deltaTs)
{
	m_Velocity.y += m_gravityComplient * m_timeParticleIsAlive;		//Veclocity of the Y is equaly to the weight of 50 x by the time its been alive (longer its alive the lower it gets)
	glm::vec3 Change = m_Velocity;								//How much the particle position should change baised on velocity, in one second
	Change *= deltaTs;											//Change is equal to the time
	m_Position += Change;										//Position of that particle added to change
	m_timeParticleIsAlive += deltaTs;		

	if ( m_timeParticleIsAlive < m_lifeLength )						//If the time particle is alive is less that length of life, return true draw new particle
	{
		return true;
	}

	return false;
}


void Particle::generateParticles(float deltaTs)
{
	m_ParticlesToCreate = m_pps * deltaTs;					//Particle to create is down to particle per square inch multiple by time
	m_count = (int)floor(m_ParticlesToCreate);				//Count is how many particles are left to create
	m_particalToDraw = m_ParticlesToCreate + m_Random;		//Particle to draw is equal to how many are in particles to create + random number 

	for (size_t i = 0; i < m_count; ++i)					//Cycle through how many are in count
	{
		_ParticleToDraw->Draw();						//Send them particles to draw

	}

	if (m_Random < m_particalToDraw )						//If the random number is less than particles to draw
	{
		_ParticleToDraw->Draw();						//Draw the particles

	}


}

void Particle::Draw()
{
	std::vector <Particle*> ParticleSystem;		//Creates a vector for them particles, the particle system

	ParticleSystem.push_back(_ParticleToDraw);	//Push them particles to draw into the vector

	for each (Particle* P in ParticleSystem)	//For each particle in particle System
	{

		m_dirX = (float)m_Random * 2.0f - 1.0f;		//Set its x Direction to 
		m_dirZ = (float)m_Random2 * 2.0f - 1.0f;    //set its random y Direction to
		m_Velocity = { m_dirX, 1, m_dirZ };		    //Velocity is equal to them directions in x and z
		glm::normalize(m_Velocity);
		m_Scale = m_speed;						    //Size of the partcile is dependant on how fast it is moving, speed is down to how long its been alive


	}

}

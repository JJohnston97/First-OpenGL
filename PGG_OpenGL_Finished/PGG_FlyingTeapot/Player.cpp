/// \ File Player.cpp
/// \ Breif Handles player set up and movement

//System Includes
#include <cmath>							//Include Cmath
//Library Include
#include <GLM/gtc/type_ptr.hpp>				//Include glew
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtx/quaternion.hpp>
//Project Includes
#include "Player.h"							//Include Player.h

Player::Player()
{
	m_thrust = 0.2f;		//Players Thrust (speed)
	m_pitch = 0.0f;		//Players Pitch
	m_roll = 0.0f;		//Players Roll


	//Initialise with direction object is facing
	m_originalFacingDir = glm::vec3(1, 0, 0);
	m_originalUpDir = glm::vec3(0, 1, 0);
	m_originalLeftDir = glm::vec3(0, 0, -1);

	
	m_velocity = glm::vec3(15.0f, 0, 0); //Initial velocity


}

Player::~Player()
{

}



void Player::Update(float deltaTs)
{
	
	float currentRoll = m_roll * deltaTs * 1.2f;			//Players Current roll, updates every frame
	float currentPitch = m_pitch * deltaTs * 1.2f;		//Players Current Pitch, Updates Every frame

	m_thrust = glm::clamp(m_thrust, 0.0f, 1.0f);		

	
	glm::vec3 currentFacingDir = glm::rotate(m_orientation, m_originalFacingDir); //Compute current facing direction vector by rotating the original facing direction by the orientation
	glm::vec3 currentLeftDir = glm::rotate(m_orientation, m_originalLeftDir);		

	m_orientation = glm::angleAxis(currentRoll, currentFacingDir) * m_orientation;		  //Roll rotation
	m_orientation = glm::angleAxis(currentPitch, currentLeftDir) * m_orientation;			  //moving up or down
	m_modelMatrix = glm::translate(glm::mat4(1), m_position) * glm::mat4_cast(m_orientation);//Add pitch rotation by rotating around the left direction axis

	currentFacingDir = currentFacingDir = glm::rotate(m_orientation, m_originalFacingDir);

	m_position += currentFacingDir * m_thrust;	//Movement

	m_modelMatrix = glm::translate(glm::mat4(1), m_position) * glm::mat4_cast(m_orientation);	//Update the current facing direction based on the new rotation

	m_invModelMatrix = glm::inverse(m_modelMatrix);




}


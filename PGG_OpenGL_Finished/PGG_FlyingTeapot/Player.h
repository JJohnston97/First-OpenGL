/// \File Player.h
/// \breif handles player movement and player position 

#ifndef __PLAYER__H_
#define __PLAYER__H_

//File Includes
//System Includes
#include <GLM/gtc/quaternion.hpp>
//Project Includes
#include "GameObject.h"				//Include Game Object Header

//Header Content
class Player : public GameObject	//Player Inherits from GameObject
{
public:
	Player();				//Constructor
	~Player();				//Destructor

	virtual void Update(float deltaTs);		//Update Function called every frame for the player

	void ChangeThrust(float value) { m_thrust += value; }		//Function used to change the players thrust
	void ChangeRoll(float value) { m_roll = value; }				//Function use to change thee players roll
	void ChangePitch(float value) { m_pitch = value; }			//Function used to change the pitch of the player

	glm::vec3 GetPosition() { return m_position; }		//Get Position function used for collision, and make the sky box fixed to the player
	glm::quat GetOrientation() { return m_orientation; }	//Orientation of the player to understand the direction the player is moving

protected:

	glm::vec3 m_velocity;		//Vector for velocity
	glm::vec3 m_originalFacingDir, m_originalUpDir, m_originalLeftDir;	//Vec3 for Possible facing directions

	glm::quat m_orientation; //Initalising Orientation quat (Quaternion of float numbers)

	float m_pitch, m_roll;    //Floats for Pitch and Roll
	float m_thrust;			//Float for Thrust

};



#endif  //_PLAYER_H_

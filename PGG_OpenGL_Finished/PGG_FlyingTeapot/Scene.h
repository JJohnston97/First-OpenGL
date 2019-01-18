/// \File Scene.h
/// \Breif Scene header used for managing all draw and update functions, also used for any object creation. Also contains the camera and light

#ifndef _SCENE_H_
#define _SCENE_H_

//File Includes
//System Includes
#include <vector>
#include <string>
//Libary Includes
#include <GLM/glm.hpp>					//This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp>			//This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>
#include <SDL/SDL.h>
//Project Includes
#include "Milk.h"						//Includes Milk Header file
#include "Player.h"						//Includes Player Ha
#include "UserInterface.h"

//Header Contents
class Scene
{
public:
	Scene();   //Constructor
	~Scene();  //Destructor

	void ChangeCameraAngleX(float value) { m_cameraAngleX += value; }	//Adjust the camera's X angle / Orientation
	void ChangeCameraAngleY(float value) { m_cameraAngleY += value; }	//Adjust the camera's Y angle / Orientation
	void PlayerCollison(GameObject *_Object1, int &Score);				//Function for Player Collision
	void Update(float deltaTs);											//Calls update on all objects in the scene
	void Draw();	                                                    //Draws the scene from the camera's point of view

	float m_X;		//Initialise float X
	float m_Y;		//Initialise float Y
	float m_Z;		//Initalise float Z
	float m_Pie;	//Initalise float Pie used for rotation
	

	SDL_Event m_e;	//SDL event, used for any sdl mouse of keyboard events
	int m_MouseX;		//Initialise Mouse X used for Mouse X position 
	int m_MouseY;		//Initialise Mouse Y used for Mouse Y position
	int m_M;			//Initialise M used for If mouse is pressed
	int m_RandomX;    //Initialise RandomX for my srand random x position, used in object set position
	int m_RandomY;	//Initialise RandomY for my srand random Y position, used in object set position
	int m_RandomX2;	//Initialise RandomX2 for my srand random x2 position, used in object set position
	int m_RandomY2;	//Initialise RandomY2 for my srand random Y2 position, used in object set position
	int m_RandomZ;	//Initialise RandomZ for my srand random Z position, used in object set position
	int m_RandomZ2;	//Initialise RandomZ2 for my srand random Z2 position, used in object set position
	int m_Score;		//Holds Players score

	//bool m_Toggle;	//Toggle used for zoom



	Player* getPlayer() { return m_player; }	//Player Pointer to get Player


protected:

	//ALL UI OBJECTS
	UI *m_Toggle;
	UI *m_HealthBar;
	UI *m_LeftBar;
	UI *m_TopBar;
	UI *m_RightBar;
	UI *m_BottomBar;
	UI *m_BottomBar02;
	UI *m_BottomBar03;
	UI *m_BottomBar04;
	UI *m_UI_Header;
	UI *m_Text01;
	UI *m_Text02;
	UI *m_Text03;
	UI *m_Text04;
	UI *m_Text05;
	UI *m_Text06;

	//ALL GAMEOBJECT OBJECTS
	GameObject *m_SkyBox;
	GameObject *m_Object1;
	GameObject *m_Object2;
	GameObject *m_Object3;
	GameObject *m_Object4;
	GameObject *m_Object5;

	std::vector<GameObject*> GOS;	//Vector Used to store, Update and Draw all my GameObjects
	std::vector<UI*> HUD;			//Vector Used to store, Update and Draw all my HUD (UI Objects)
	
	Player *m_player;				//Initialise Player
	
	glm::mat4 m_viewMatrix;			//This matrix represents the camera's position and orientation
	glm::mat4 m_projMatrix;			//This matrix is like the camera's lens
	glm::mat4 m_projMatrixOrtho;		//Projection Matrix used for Orthographic rendering
	glm::mat4 m_ortho;				//Mat 4 used for matrix ortho comparision

	glm::vec3 m_lightPosition;		//Position of the single point-light in the scene
	glm::vec3 m_lightPosition2;
	glm::quat m_cameraOrientation;

	float m_cameraAngleX, m_cameraAngleY;	//Current rotation information about the camera

};

#endif //_SCENE_H_
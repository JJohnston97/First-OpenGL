/// \File Scene.cpp
/// \Breif File that handles all game object management, main file for game content

//System Includes
#include <iostream>				//Include for Debug
#include <Windows.h>			//Include Windows.h
#include <time.h>				//Include Time.h for srand
//Library Inlcudes
#include <SDL/SDL.h>			//Include SDL2
#include <SDL_mixer.h>			//Include for Audio
//Project Includes
#include "Milk.h"				//Include Milk.h for milk objects
#include "ParticleSystem.h"		//Include particlesystem.h for Particle
#include "Scene.h"				//Include Scene.h
#include "UserInterface.h"		//Include UserInterface for UI Objects


Scene::Scene()
{
	m_Score = 0;									//Score Is first set to 0
	m_Pie = 3.14159265358979323846;				//Setting pie for rotations as rotations happen in raidons, pie is equal to 180 degrees
	m_cameraAngleX = 0.3f, m_cameraAngleY = 1.5f;
	m_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);			  //Set up a projection matrix
	m_projMatrixOrtho = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);   //Set up Orthographic view
	m_lightPosition = glm::vec3(1, 1, 1);									  //Position of the light, in world-space

	m_MouseX = { 0 };									//Mouse X set to 0 
	m_MouseY = { 0 };									//Mouse Y set to 0								
	m_M = SDL_GetMouseState(&m_MouseX, &m_MouseY) & 1;	//M is equal to mouse click if equal to 1

	srand(time(NULL));								//Start and srand
	m_RandomX = (rand() % 1000 + 1);					//Random X, Y and Z positions
	m_RandomY = (rand() % 600 + 1);
	m_RandomX2 = (rand() % 850 + 1);
	m_RandomY2 = (rand() % 1200 + 1);
	m_RandomZ = (rand() % 400 + 1);
	m_RandomZ2 = (rand() % 200 + 1);

	//Game Objects
	m_SkyBox = new GameObject();		
	m_Object1 = new GameObject();
	m_Object2 = new GameObject();
	m_Object3 = new GameObject();
	m_Object4 = new GameObject();
	m_Object5 = new GameObject();

	//GameObjects push back in Object vector
	GOS.push_back(m_Object1);
	GOS.push_back(m_Object2);
	GOS.push_back(m_Object3);
	GOS.push_back(m_Object4);
	GOS.push_back(m_Object5);

	//Create the material for the game object																		
	Material *modelMaterial = new Material();																		
	Material *Object1Mat = new Material();																																							   																				
	Material *teapotMaterial = new Material();																	
	Material *SkyBoxMat = new Material();	
	Material *Yellow = new Material();
																																																																	
	//Send material to shaders																		
	modelMaterial->getShader()->LoadShaders("VertShader.txt", "FragShader.txt");																		
	teapotMaterial->getShader()->LoadShaders("VertShader.txt", "FragShader.txt");		
	SkyBoxMat->getShader()->LoadShaders("VertShader.txt", "FragShader.txt");
	Object1Mat->getShader()->LoadShaders("VertShader.txt", "FragShader.txt");
	Yellow->getShader()->LoadShaders("VertShader.txt", "FragShader.txt");

	//Set the diffuse colour 
	teapotMaterial->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));		 		 
	modelMaterial->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	SkyBoxMat->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));							
	Object1Mat->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));						
	Yellow->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));																				
	
	//Set Specular Colour
	modelMaterial->setSpecularColour(glm::vec3(2.0, 2.0, 2.0));

	//Set the texture
	modelMaterial->setTexture("White.bmp");
	teapotMaterial->setTexture("FlyingTeapotColour.bmp");
	SkyBoxMat->setTexture("Sky_Box_UV.bmp");
	Object1Mat->setTexture("Yellow.bmp");
	
	
	//Set Second Texture for Multi Texture
	modelMaterial->setTexture2("Box2.bmp");
	teapotMaterial->setTexture2("Box2.bmp");

	//Light Position
	modelMaterial->setLightPosition(m_lightPosition);
	teapotMaterial->setLightPosition(m_lightPosition); 		
	Yellow->setLightPosition(m_lightPosition);
	SkyBoxMat->setLightPosition(m_lightPosition);
	Object1Mat->setLightPosition(m_lightPosition);
															
	//The mesh is the geometry for the object
	Mesh *modelMesh = new Mesh();
	Mesh *SkyBoxMesh = new Mesh();
	Mesh *Object1Mesh = new Mesh();
	Mesh *Object2Mesh = new Mesh();
	Mesh *Object3Mesh = new Mesh();
	Mesh *Object4Mesh = new Mesh();
	Mesh *Object5Mesh = new Mesh();


	//Load from OBJ file. This must have triangulated geometry
	modelMesh->LoadOBJ("Player01.obj");
	SkyBoxMesh->LoadOBJ("SkyBox.obj");
	Object1Mesh->LoadOBJ("Milk.obj");
	Object2Mesh->LoadOBJ("Milk.obj");
	Object3Mesh->LoadOBJ("Milk.obj");
	Object4Mesh->LoadOBJ("Milk.obj");
	Object5Mesh->LoadOBJ("Milk.obj");


	//Object IS player type
	m_player = new Player();

	
	//Object to mesh
	m_player->setMesh(modelMesh);
	m_SkyBox->setMesh(SkyBoxMesh);
	m_Object1->setMesh(Object1Mesh);
	m_Object2->setMesh(Object2Mesh);
	m_Object3->setMesh(Object3Mesh);
	m_Object4->setMesh(Object4Mesh);
	m_Object5->setMesh(Object5Mesh);
	

	//Material to game object
	//Tell the game object to use this material               		
	m_player->setMaterial(teapotMaterial);				
	m_SkyBox->setMaterial(SkyBoxMat);
	m_Object1->setMaterial(Object1Mat);
	m_Object2->setMaterial(Object1Mat);
	m_Object3->setMaterial(Object1Mat);
	m_Object4->setMaterial(Object1Mat);
	m_Object5->setMaterial(Object1Mat);

	//Set position
	m_player->setPosition(-100.0f, 100.0f, 0.0f);
	m_SkyBox->setPosition(-50.0f, 50.0f, 0.0f);
	m_Object1->setPosition(100.0f, 400.0f, m_RandomZ);
	m_Object2->setPosition(m_RandomX2, -150.0f, -200.0f);
	m_Object3->setPosition(-m_RandomX, m_RandomY, 70.0f);
	m_Object4->setPosition(250.0f, -350.0f, m_RandomZ2);
	m_Object5->setPosition(-500.0f, -m_RandomY2, 0.0f);

	//Set Scale
	m_SkyBox->setScale(5000, 5000, 5000);
	m_Object1->setScale(10, 10, 10);
	m_Object2->setScale(10, 10, 10);
	m_Object3->setScale(10, 10, 10);
	m_Object4->setScale(10, 10, 10);
	m_Object5->setScale(10, 10, 10);
	m_player->setScale(1, 1, 1);
	
	//Set Rotation
	m_player->setRotation(m_Pie / 2, 0.0f, m_Pie/2);
	m_SkyBox->setRotation(m_Pie / 2, 0.0f, 0.0f);
	
	
	//User Interface
	m_Toggle = new UI();
	m_HealthBar = new UI();
	m_LeftBar = new UI();
	m_RightBar = new UI();
	m_TopBar = new UI();
	m_BottomBar = new UI();
	m_BottomBar02 = new UI();
	m_BottomBar03 = new UI();
	m_BottomBar04 = new UI();
	m_UI_Header = new UI();
	m_Text01 = new UI();
	m_Text02 = new UI();
	m_Text03 = new UI();
	m_Text04 = new UI();
	m_Text05 = new UI();
	m_Text06 = new UI();

	//Push back UI in HUD Vector
	HUD.push_back(m_Toggle);
	HUD.push_back(m_HealthBar);
	HUD.push_back(m_LeftBar);
	HUD.push_back(m_RightBar);
	HUD.push_back(m_TopBar);
	HUD.push_back(m_BottomBar);
	HUD.push_back(m_BottomBar02);
	HUD.push_back(m_BottomBar03);
	HUD.push_back(m_BottomBar04);
	HUD.push_back(m_UI_Header);
	HUD.push_back(m_Text06);

	//New UI Material
	Material *ButtonMat = new Material();
	Material *HealthMat = new Material();
	Material *LeftMat = new Material();
	Material *RightMat = new Material();
	Material *TopMat = new Material();
	Material *UI_HeaderMat = new Material();
	Material *RedMat = new Material();

	//UI to shaders
	ButtonMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");
	HealthMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");
	LeftMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");
	RightMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");
	UI_HeaderMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");
	RedMat->getShader()->LoadShaders("uivert.txt", "uifrag.txt");

	//Set UI Diff Colour
	ButtonMat->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));							//Note that the diffuse colour set with the line above will be multiplied by the texture colour
	HealthMat->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	LeftMat->setDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	RightMat->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	UI_HeaderMat->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	RedMat->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

	//Set UI Texture
	ButtonMat->setTexture("Zoom.bmp");
	HealthMat->setTexture("HealthBar_UV.bmp");
	LeftMat->setTexture("Grey_Bar.bmp");
	RightMat->setTexture("Grey_Bar.bmp");
	UI_HeaderMat->setTexture("Grey_Bar.bmp");
	RedMat->setTexture("Red.bmp");

	//New UI Mesh
	Mesh *ButtonMesh = new Mesh();
	Mesh *HealthMesh = new Mesh();
	Mesh *LeftMesh = new Mesh();
	Mesh *RightMesh = new Mesh();
	Mesh *TopMesh = new Mesh();
	Mesh *BottomMesh = new Mesh();
	Mesh *BottomMesh02 = new Mesh();
	Mesh *BottomMesh03 = new Mesh();
	Mesh *BottomMesh04 = new Mesh();
	Mesh *HeaderMesh = new Mesh();
	Mesh *NumberOneMesh = new Mesh();
	Mesh *NumberTwoMesh = new Mesh();
	Mesh *NumberThreeMesh = new Mesh();
	Mesh *NumberFourMesh = new Mesh();
	Mesh *NumberFiveMesh = new Mesh();
	Mesh *Collected = new Mesh();

	//UI load OBJ
	ButtonMesh->LoadOBJ("ui.obj");
	HealthMesh->LoadOBJ("HealthBar.obj");
	LeftMesh->LoadOBJ("UI_Edge.obj");
	RightMesh->LoadOBJ("UI_Edge.obj");
	TopMesh->LoadOBJ("UI_Edge.obj");
	BottomMesh->LoadOBJ("UI_Edge.obj");
	BottomMesh02->LoadOBJ("UI_Edge.obj");
	BottomMesh03->LoadOBJ("UI_Edge.obj");
	BottomMesh04->LoadOBJ("UI_Edge.obj");
	HeaderMesh->LoadOBJ("UI_Header.obj");
	NumberOneMesh->LoadOBJ("Number1.obj");
	NumberTwoMesh->LoadOBJ("Number2.obj");
	NumberThreeMesh->LoadOBJ("Number3.obj");
	NumberFourMesh->LoadOBJ("Number4.obj");
	NumberFiveMesh->LoadOBJ("Number5.obj");
	Collected->LoadOBJ("Collected.obj");

	//UI Mesh
	m_Toggle->setUIMesh(ButtonMesh);
	m_HealthBar->setUIMesh(HealthMesh);
	m_LeftBar->setUIMesh(LeftMesh);
	m_RightBar->setUIMesh(RightMesh);
	m_TopBar->setUIMesh(TopMesh);
	m_BottomBar->setUIMesh(BottomMesh);
	m_BottomBar02->setUIMesh(BottomMesh02);
	m_BottomBar03->setUIMesh(BottomMesh03);
	m_BottomBar04->setUIMesh(BottomMesh04);
	m_UI_Header->setUIMesh(HeaderMesh);
	m_Text01->setUIMesh(NumberOneMesh);
	m_Text02->setUIMesh(NumberTwoMesh);
	m_Text03->setUIMesh(NumberThreeMesh);
	m_Text04->setUIMesh(NumberFourMesh);
	m_Text05->setUIMesh(NumberFiveMesh);
	m_Text06->setUIMesh(Collected);

	//UI Materials
	m_Toggle->setUIMaterial(ButtonMat);
	m_HealthBar->setUIMaterial(HealthMat);
	m_LeftBar->setUIMaterial(LeftMat);
	m_RightBar->setUIMaterial(RightMat);
	m_TopBar->setUIMaterial(RightMat);
	m_BottomBar->setUIMaterial(RightMat);
	m_BottomBar02->setUIMaterial(RightMat);
	m_BottomBar03->setUIMaterial(RightMat);
	m_BottomBar04->setUIMaterial(RightMat);
	m_UI_Header->setUIMaterial(UI_HeaderMat);
	m_Text01->setUIMaterial(RedMat);
	m_Text02->setUIMaterial(RedMat);
	m_Text03->setUIMaterial(RedMat);
	m_Text04->setUIMaterial(RedMat);
	m_Text05->setUIMaterial(RedMat);
	m_Text06->setUIMaterial(RedMat);

	//Set Ui Position
	m_Toggle->setUIPosition(770.0f, 775.0f, 0.0f);
	m_HealthBar->setUIPosition(100.0f, 760.0f, 0.0f);
	m_LeftBar->setUIPosition(0.0f, 100.0f, 0.0f);
	m_RightBar->setUIPosition(800.0f, 100.0f, 0.0f);
	m_TopBar->setUIPosition(50.0f, 6.0f, 0.0f);
	m_BottomBar->setUIPosition(100.0f, 700.0f, 0.0f);
	m_BottomBar02->setUIPosition(200.0f, 750.0f, 0.0f);
	m_BottomBar03->setUIPosition(200.0f, 790.0f, 0.0f);
	m_UI_Header->setUIPosition(400.0f, 10.0f, 0.0f);
	m_Text01->setUIPosition(40.0f, 70.0f, 0.0f);
	m_Text02->setUIPosition(60.0f, 70.0f, 0.0f);
	m_Text03->setUIPosition(80.0f, 70.0f, 0.0f);
	m_Text04->setUIPosition(102.0f, 70.0f, 0.0f);
	m_Text05->setUIPosition(122.0f, 70.0f, 0.0f);
	m_Text06->setUIPosition(42.0f, 30.0f, 0.0f);

	//UI Scale
	m_Toggle->setUIScale(50, 50, 1);
	m_HealthBar->setUIScale(100, 100, 1);
	m_LeftBar->setUIScale(20, 1500, 1);
	m_RightBar->setUIScale(20, 1300, 1);
	m_TopBar->setUIScale(1000, 20, 1);
	m_BottomBar->setUIScale(100, 20, 1);
	m_BottomBar02->setUIScale(20, 120, 1);
	m_BottomBar03->setUIScale(548, 20, 1);
	m_UI_Header->setUIScale(100, 100, 1);
	m_Text01->setUIScale(20, 20, 1);
	m_Text02->setUIScale(20, 20, 1);
	m_Text03->setUIScale(20, 20, 1);
	m_Text04->setUIScale(20, 20, 1);
	m_Text05->setUIScale(20, 20, 1);
	m_Text06->setUIScale(20, 20, 1);

}

Scene::~Scene()
{
	
}

void Scene::Update(float deltaTs)
{
	m_player->Update(deltaTs); //Sending the Player Object to Update Function
	

	for (int h = 0; h < HUD.size(); ++h)		//For Loop to Loop HUD size
	{

		HUD.at(h)->Update(deltaTs);				//Send each item to update

	}

	for (int x = 0; x < GOS.size(); ++x)		//For loop to loop over GOS size
	{

		GOS.at(x)->Update(deltaTs);				//Send each item to Update

	}

	for (int x = 0; x < GOS.size(); ++x)		//Loops GOS size
	{

		if ( GOS.at(x)->isDestroyed() )			//For each object that is destroyed
		{
			delete GOS.at(x);					//Deleted that Object from the vector
			GOS.erase(GOS.begin() + x);			//Move to the next object
			x--;								//So it doesn't miss one x--
		
		}

	}

	for (int x = 0; x < GOS.size(); ++x)
	{
	
		PlayerCollison(GOS.at(x), m_Score);       //Checks player collision every frame

		if (m_Score == 1 )						//If score is equal to 1 
		{
		
			m_Text01->Update(deltaTs);			//Send this to update and will draw

		} 
		else if (m_Score == 2 ) {				//If Score is equal to 2

		
			m_Text02->Update(deltaTs);			//Send this to Update and will draw

		}
		else if (m_Score == 3 ) {				//If score is 3


			m_Text03->Update(deltaTs); 
		}
		else if (m_Score == 4 ) {				//If score it 4

			m_Text04->Update(deltaTs);

		}
		else if (m_Score == 5 )					//If score is 5
		{

			m_Text05->Update(deltaTs);

		}

	}

	glm::vec3 playerPos = m_player->GetPosition();						//Gets player position into vec3 playerPos
	glm::quat playerOrientation = m_player->GetOrientation();			//Gets player ori into playerOrientation

	m_SkyBox->setPosition(playerPos);			//SkyBox Pos is equal to player position so you can't fly out of it 
	m_SkyBox->Update(deltaTs);					//Need to update the draw again


	m_cameraOrientation = glm::slerp(m_cameraOrientation, -playerOrientation, 7.2f*deltaTs);

	// Build the viewing matrix:
	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10.0f));			//Provides offset away from player object
	m_viewMatrix = glm::rotate(m_viewMatrix, m_cameraAngleX, glm::vec3(1, 0, 0));		//Allows player to rotate camera using player object as pivot
	m_viewMatrix = glm::rotate(m_viewMatrix, m_cameraAngleY, glm::vec3(0, 1, 0));
	m_viewMatrix = m_viewMatrix * glm::mat4_cast(glm::inverse(m_cameraOrientation));	//Orient towards player direction
	m_viewMatrix = glm::translate(m_viewMatrix, -playerPos);                          // Move to player's position


	m_MouseX = { 0 };			//Set mouse to 0
	m_MouseY = { 0 };			//Set Mouse to 0								
	m_M = SDL_GetMouseState(&m_MouseX, &m_MouseY) & 1;
	
	if (m_M == 1 )
	{
		if ( (m_MouseX > 750) && (m_MouseX < 800) && (m_MouseY > 750) && (m_MouseY < 800) )	//If you click between the paramiters
		{
			
			m_viewMatrix = glm::translate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, -3.5)), m_cameraAngleX, glm::vec3(180, 0, 0)), m_cameraAngleY, glm::vec3(0, 1, 0)), -playerPos);
		}
	}

}

void Scene::Draw()
{
	
	m_player->Draw(m_viewMatrix, m_projMatrix); //Draws the player 

	m_SkyBox->Draw(m_viewMatrix, m_projMatrix); //Draws sky box


	for (int h = 0; h < HUD.size(); ++h)
	{

		HUD.at(h)->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);	//Draws all the items in HUD with Ortho

	}

	for (int x = 0; x < GOS.size(); ++x)
	{

		GOS.at(x)->Draw(m_viewMatrix, m_projMatrix);				//Draws all the Items in GOS

	}

	
	m_Text01->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);			//Text are drawn on their own because they are based on score
	m_Text02->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);
	m_Text03->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);
	m_Text04->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);
	m_Text05->DrawOrtho(m_viewMatrix, m_projMatrixOrtho);
	

}

void Scene::PlayerCollison(GameObject *_Object1, int &Score)
{
	if ( m_player->GetPosition().x <= ( _Object1->getPosition().x + _Object1->getScale().x / 1 )		//If the player x position greater than or equal to the object x position + a whole of the object
		&& m_player->GetPosition().x >= (_Object1->getPosition().x) - _Object1->getScale().x /1 )		//Bounding Box collsiion
	{ 
		if( m_player->GetPosition().y <= ( _Object1->getPosition().y + _Object1->getScale().y / 1 )			//Using Y and Z because my objects are in space and could be hit from any position
			&& m_player->GetPosition().y >= ( _Object1->getPosition().y - _Object1->getScale().y / 1) )
		{
			if ( m_player->GetPosition().z <= ( _Object1->getPosition().z + _Object1->getScale().z / 1 )
				&& m_player->GetPosition().z >= ( _Object1->getPosition().z - _Object1->getScale().z / 1) )	//Add a whole of the scale and minus a whole of the scale for bounding box
			{
				std::cout << " Hit " << std::endl;
				_Object1->setDestroy(true);			//When hit the object set destory is set to true
				Score ++;							//Score add 1
				std::cout << "Score = " << Score << std::endl;
			}
		}
	}
}






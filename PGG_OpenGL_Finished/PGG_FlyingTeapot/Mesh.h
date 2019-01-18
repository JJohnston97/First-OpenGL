/// \File Mesh.h
/// \Breif Used to load a mesh from OBJ file and keeping a reference for it

#ifndef __MESH__H_
#define __MESH__H_
//System Includes
#include <string>
//Libary Includes
#include <GLM/glm.hpp>
#include <SDL/SDL.h>
//Porject Includes
#include "glew.h"


class Mesh
{
public:

	Mesh();		//Construtor
	~Mesh();	//Destructor

	void LoadOBJ(std::string filename);		//Used to load in OBJ's, they must be triangulated
	void Draw();                            //Draws the Mesh, Must have shaders applied

protected:

	
	GLuint m_VAO;	            //OpenGL Vertex Array Object stores multipul VBO's 

	unsigned int m_numVertices;  //Number of Vertices in the Mesh

};


#endif //_MESH_H_

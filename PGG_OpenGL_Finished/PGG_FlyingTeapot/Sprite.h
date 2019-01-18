/// \ file Sprite.h
/// \brief Mananges position, texture and creations of my sprites

#ifndef _SPRITE_H
#define _SPRITE_H

//libary includes
#include <SDL.h>														//Includes the sdl libary



//header content
class Sprite
{

public:
	Sprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h);			//Constructor
	~Sprite();																																				//Destructor 


	virtual void Draw();

	void SetX(int _x) { m_position.x = _x; }								//Asking for the x and y positions for the sprite to be drawn at
	void SetY(int _y) { m_position.y = _y; }

	int GetX() { return m_position.x; }
	int GetY() { return m_position.y; }





protected:

	SDL_Renderer* m_renderer;				//Sdl Render using for drawing
	SDL_Texture* m_image;						//Image used by this sprite

	SDL_Rect m_position;					  //x&y position and width, height of this sprite

};

#endif // !_SPRITE_H
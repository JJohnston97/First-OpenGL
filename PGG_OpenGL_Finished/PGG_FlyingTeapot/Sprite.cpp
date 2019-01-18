#include "Sprite.h"																			//Includes sprite

Sprite::Sprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h)		//Consutor of the class
{
	SDL_Surface* bmpFile = SDL_LoadBMP(_file);										//Loads int he bmp file
	m_image = SDL_CreateTextureFromSurface(_renderer, bmpFile);		//Render the image to the window
	SDL_FreeSurface(bmpFile);

	m_position.x = _x;												//Initial Position & width and height of the sprite
	m_position.y = _y;												//Based on incoming parameters
	m_position.w = _w;
	m_position.h = _h;

	m_renderer = _renderer;

}

Sprite::~Sprite()													//Destructor function is being called to destory a sprite
{

	if (m_image)
		SDL_DestroyTexture(m_image);								//Destory Sprite


}


void Sprite::Draw()													//Draws the sprite image to the screen
{

	if (m_image)
		SDL_RenderCopy(m_renderer, m_image, NULL, &m_position);


}
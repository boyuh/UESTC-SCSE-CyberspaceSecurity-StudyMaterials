#include "SpriteBase.h"

SpriteBase::SpriteBase(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dx = dx;
	this->dy = dy;
	this->img = img;
	r = r1;
}

SpriteBase::SpriteBase(SpriteBase & sprite)
{
	x = sprite.x;
	y = sprite.y;
	width = sprite.width;
	height = sprite.height;
	dx = sprite.dx;
	dy = sprite.dy;
	img = sprite.img;
	r = sprite.r;
}

SpriteBase::~SpriteBase()
{

}

void SpriteBase::drawSprite(int width, int height)
{
	putImageScale(img, x, y, width, height);
}

void SpriteBase::drawSprite()
{
	putImageScale(img, x, y, width, height);
}

rect SpriteBase::getRect()
{
	rect r = { x, y, width, height };
	return r;
}
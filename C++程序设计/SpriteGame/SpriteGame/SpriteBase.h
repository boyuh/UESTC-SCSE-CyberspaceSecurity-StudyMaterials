#pragma once
#include"acllib.h"
class SpriteBase
{
protected:
	int x, y;
	int width, height;
	int dx, dy;
	ACL_Image *img;
	rect r;
public:
	SpriteBase(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1);
	SpriteBase(SpriteBase & base);
	virtual ~SpriteBase();

	virtual void move(rect r)=0;
	void drawSprite(int width, int height);
	void drawSprite();
	rect getRect();
};


#pragma once
#include"acllib.h"
#include "AutoSprite.h"

class CAvoidSprite :
	public CAutoSprite
{
	bool mynear(rect ur);
public:
	CAvoidSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1,int score, int heart);
	CAvoidSprite(CAvoidSprite &sprite);
	virtual ~CAvoidSprite();

	void move(rect ur);
};


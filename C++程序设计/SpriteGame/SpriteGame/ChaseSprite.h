#pragma once
#include "AutoSprite.h"
class CChaseSprite :
    public CAutoSprite
{
	bool mynear(rect ur);
public:
	CChaseSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1, int score, int heart);
	CChaseSprite(CChaseSprite& sprite);
	virtual ~CChaseSprite();

	void move(rect ur);
};


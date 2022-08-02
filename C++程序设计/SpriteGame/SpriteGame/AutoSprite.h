#pragma once
#include "SpriteBase.h"
class CAutoSprite :
	public SpriteBase
{
	int mark;
	int score;
	int heart;
	int dxx, dyy;
public:
	CAutoSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1,int score, int heart);
	CAutoSprite(CAutoSprite &sprite);
	~CAutoSprite();

	void move(rect r);
	int getScore();
	int getHeart();

	int distance(int r1_x, int r1_y, int r1_w, int r1_h, int r2_x, int r2_y, int r2_w, int r2_h);
};


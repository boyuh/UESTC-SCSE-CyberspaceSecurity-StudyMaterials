#include "AutoSprite.h"
#include<math.h>

CAutoSprite::CAutoSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1,int score,int heart):SpriteBase(x,y,width,height,dx,dy,img,r1)
{
	this->score = score;
	this->heart = heart;
	this->mark = 1;
	this->dxx = dx;
	this->dyy = dy;
}

CAutoSprite::CAutoSprite(CAutoSprite &sprite):SpriteBase(sprite)
{
	score = sprite.score;
	heart = sprite.heart;
	mark = 1;
	dxx = sprite.dx;
	dyy = sprite.dy;
}

CAutoSprite::~CAutoSprite()
{
}

void CAutoSprite::move(rect r1)
{
	if (dx==0 && dy==0 && !(distance(x, y, width, height, r1.x, r1.y, r1.width, r1.height) && (x<=r.x || x>=(r.x + r.width - width) || y<=r.y || y>=(r.y + r.height - height)))) {
		if (x == r.x || y == r.y) {
			dx = -dxx;
			dy = -dyy;
		}
		if (x == r.x + r.width - width || y == r.y + r.height - height) {
			dx = dxx;
			dy = dyy;
		}
		mark = 1;
	}
	if (!distance(x, y, width, height, r1.x, r1.y, r1.width, r1.height) && (x<=r.x || x>=(r.x + r.width - width))) { dx *= -1; mark = 1; }
	if (!distance(x, y, width, height, r1.x, r1.y, r1.width, r1.height) && (y<=r.y || y>=(r.y + r.height - height))) { dy *= -1; mark = 1; }
	if (mark == 1 && distance(x, y, width, height, r1.x, r1.y, r1.width, r1.height) && !(x<=r.x || x>=(r.x + r.width - width)|| y<=r.y || y>=(r.y + r.height - height))) {
		dx *= -1;
		dy *= -1;
		mark = 0;
	}
	if (distance(x, y, width, height, r1.x, r1.y, r1.width, r1.height) && (x<=r.x || x>=(r.x + r.width - width) || y<=r.y || y>=(r.y + r.height - height))) {
		if (x < r.x) x = r.x;
		if (x > (r.x + r.width - width)) x = r.x + r.width - width;
		if(y < r.y) y = r.y;
		if (y > (r.y + r.height - height)) y = r.y + r.height - height;
		dx = 0;
		dy = 0;
		mark = 0;
	}
	x += dx;
	y += dy;
}

int CAutoSprite::getScore()
{
	return score;
}

int CAutoSprite::getHeart()
{
	return heart;
}

int CAutoSprite::distance(int r1_x, int r1_y, int r1_w, int r1_h, int r2_x, int r2_y, int r2_w, int r2_h) {
	double r1_o_x, r1_o_y, r2_o_x, r2_o_y;
	double d_1_2, d_0;
	double d;
	r1_o_x = r1_x + (double)r1_w / 2;
	r1_o_y = r1_y + (double)r1_h / 2;
	r2_o_x = r2_x + (double)r2_w / 2;
	r2_o_y = r2_y + (double)r2_h / 2;
	d_1_2 = sqrt(pow(r1_o_x - r2_o_x, 2) + pow(r1_o_y - r2_o_y, 2));
	d_0 = (sqrt(pow((double)r1_w, 2) + pow((double)r1_h, 2)) + sqrt(pow((double)r2_w, 2) + pow((double)r2_h, 2))) / 2;
	d = r2_w / 4;
	if (d_1_2 <= d_0 + d)return 1;
	return 0;
}
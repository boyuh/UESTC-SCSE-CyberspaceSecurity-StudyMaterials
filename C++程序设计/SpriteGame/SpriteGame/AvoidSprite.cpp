#include "AvoidSprite.h"
#include<math.h>

CAvoidSprite::~CAvoidSprite()
{
}

CAvoidSprite::CAvoidSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image *img, rect r1,int score, int heart)
	:CAutoSprite(x, y, width, height, dx, dy, img, r1,score,heart)
{

}

CAvoidSprite::CAvoidSprite(CAvoidSprite &sprite)
	:CAutoSprite(sprite)
{

}

void CAvoidSprite::move(rect ur)
{
		if ((x < r.x)) { x = r.x + r.width - width;}
		if ((x > (r.x + r.width - width))) { x = r.x;}
		if ((y < r.y)) { y = r.y + r.height - height;}
		if ((y > (r.y + r.height - height))) { y = r.y;}
		if (mynear(ur)) {
			if (x < ur.x)dx = -abs(dx);
			else if(x > ur.x)dx = abs(dx);
			if (y < ur.y)dy = -abs(dy);
			else if(y > ur.y) dy = abs(dy);
		}
		x += dx;
		y += dy;
}

bool CAvoidSprite::mynear(rect ur)
{
	double r1_o_x, r1_o_y, r2_o_x, r2_o_y;
	double d_1_2, d_0;
	double d;
	r1_o_x = x + (double)width / 2;
	r1_o_y = y + (double)height / 2;
	r2_o_x = ur.x + (double)ur.width / 2;
	r2_o_y = ur.y + (double)ur.height / 2;
	d_1_2 = sqrt(pow(r1_o_x - r2_o_x, 2) + pow(r1_o_y - r2_o_y, 2));
	d_0 = (sqrt(pow((double)width, 2) + pow((double)height, 2)) + sqrt(pow((double)ur.width, 2) + pow((double)ur.height, 2))) / 2;
	d = ur.width;
	if (d_1_2 <= d_0 + d)return true;
	return false;
}
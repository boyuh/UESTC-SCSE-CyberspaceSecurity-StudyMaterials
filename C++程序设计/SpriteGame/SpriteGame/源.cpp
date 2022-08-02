#include"acllib.h"
#include"AutoSprite.h"
#include"UsrSprite.h"
#include"AvoidSprite.h"
#include"ChaseSprite.h"
#include<time.h>
#include<stdio.h>
#include<math.h>

const int maxNum = 120;
const int winWidth = 800, winHeight = 600;
CAutoSprite *autosprite[maxNum] = { 0 };
CUsrSprite *usr = NULL;
int autoWidth = 50, autoHeight = 50;
int usrWidth = 80, usrHeight = 80;
ACL_Image img, imgUsr, imgDuck, imgDog, imgHeart, imgSuccess, imgFail, imgBegin;
rect winRect;
void timerEvent(int id);
void cancelTimer(int id);
void createData(CAutoSprite **autoSprite);
void createData(CUsrSprite **usr);
void keyEvent(int key, int event);
void paint();
int nowNum = 0;
int getBigger_mark = 0;
int create_mark = 0;
int create_mark2 = 0;
int begin_mark = 0;
int begin_mark2 = 1;

int Setup()
{
	winRect.x = DEFAULT;
	winRect.y = DEFAULT;
	winRect.width = winWidth;
	winRect.height = winHeight;
	initWindow("Sprite Game   º«²©Óî 2019040708023", DEFAULT, DEFAULT, winWidth, winHeight);
	srand((unsigned)time(NULL));
	
	loadImage("jerry.bmp", &img);
	loadImage("tom.bmp", &imgUsr);
	loadImage("duck.jpg", &imgDuck);
	loadImage("dog.bmp", &imgDog);
	loadImage("heart.bmp", &imgHeart);
	loadImage("success.jpg", &imgSuccess);
	loadImage("fail.jpg", &imgFail);
	loadImage("begin.jpg", &imgBegin);

	createData(&usr);
	createData(autosprite);
	registerTimerEvent(timerEvent);
	registerKeyboardEvent(keyEvent);
	startTimer(0, 40);
	startTimer(1, 1000);
	return 0;
}

void timerEvent(int id)
{
	if (begin_mark == 0) {
		int begin_width = 550, begin_height = 442;
		beginPaint();
		clearDevice();
		putImageScale(&imgBegin, (winRect.x + winRect.width - begin_width) / 2, (winRect.y + winRect.height - begin_height) / 2, begin_width, begin_height);
		endPaint();
	}
	else {
		if (usr->getHeart() < 0) {
			char txt[50];
			int fail_width = 550, fail_height = 324;
			beginPaint();
			clearDevice();
			putImageScale(&imgFail, (winRect.x + winRect.width - fail_width) / 2, (winRect.y + winRect.height - fail_height) / 2, fail_width, fail_height);
			sprintf_s(txt, "Final scores:%d", usr->getScore());
			setTextSize(20);
			paintText(10, 10, txt);
			endPaint();
			begin_mark2 = -1;
		}
		else {
			if (usr->getScore() >= 100) {
				char txt[50];
				int success_width = 550, success_height = 324;
				beginPaint();
				clearDevice();
				putImageScale(&imgSuccess, (winRect.x + winRect.width - success_width) / 2, (winRect.y + winRect.height - success_height) / 2, success_width, success_height);
				sprintf_s(txt, "Final scores:%d    heart:%d", usr->getScore(), usr->getHeart());
				setTextSize(20);
				paintText(10, 10, txt);
				endPaint();
				begin_mark2 = -1;
			}
			else {
				int i = 0;
				switch (id)
				{
				case 0:
					for (i = 0; i < nowNum; ++i)
						if (autosprite[i])
						{
							rect ur = usr->getRect();
							autosprite[i]->move(ur);
							if (usr->collision(autosprite[i]->getRect()))
							{
								int s = autosprite[i]->getScore();
								int t = autosprite[i]->getHeart();
								if (usr) {
									usr->addScore(s);
									usr->addHeart(t);
								}
								delete(autosprite[i]);
								autosprite[i] = NULL;
							}
						}
					break;
				case 1:
					if (nowNum < maxNum)
					{
						createData(autosprite);
					}
					break;
				}
				paint();
			}
		}
	}
}

void createData(CUsrSprite** usr)
{
	int x = rand() % winWidth - autoWidth;
	if (x < 0)x = 0;
	int y = rand() % winHeight - autoHeight;
	if (y < 0)y = 0;
	int dx = 4;
	int dy = 4;
	*usr = new CUsrSprite(x, y, usrWidth, usrHeight, dx, dy, &imgUsr, winRect);

}

void createData(CAutoSprite **autoSprite)
{
	int x = rand() % winWidth - autoWidth;
	if (x < 0)x = 0;
	int y = rand() % winHeight - autoHeight;
	if (y < 0)y = 0;
	int dx = rand() % 3 + 1;
	int dy = rand() % 3 + 1;
	int sc = usr->getScore();
	if (!((sc >= 20 && sc < 30 && create_mark < 1) || (sc >= 30 && sc < 50 && create_mark < 2) || (sc >= 50 && sc < 70 && create_mark < 3) || (sc >= 70 && sc < 90 && create_mark < 4) || (sc >= 80 && sc < 90 && create_mark < 5) || (sc >= 90 && sc < 100 && create_mark < 6)|| (sc >= 25 && sc < 75 && create_mark2 < 1) || (sc >= 75 && sc < 100 && create_mark2 < 2))) {
		int t = rand() % 100;
		if (t < 90)
			autosprite[nowNum++] = new CAutoSprite(x, y, autoWidth, autoHeight, dx, dy, &img, winRect, 1, 0);
		else
			autosprite[nowNum++] = new CAvoidSprite(x, y, autoWidth, autoHeight, 2.5, 2.5, &imgDuck, winRect, 5, 0);
	}
	if ((sc >= 20&& sc < 30 && create_mark<1) || (sc >= 30 && sc < 50 && create_mark < 2) || (sc >= 50 && sc < 70 && create_mark < 3) || (sc >= 70 && sc < 90 && create_mark < 4) || (sc >= 80 && sc < 90 && create_mark < 5) || (sc >= 90 && sc < 100 && create_mark < 6)) {
		autosprite[nowNum++] = new CChaseSprite(x, y, 1.5*autoWidth, 1.5*autoHeight, 2, 2, &imgDog, winRect, 0, -1);
		create_mark++;
	}
	if ((sc >= 25 && sc < 75 && create_mark2 < 1) || (sc >= 75 && sc < 100 && create_mark2 < 2)) {
		autosprite[nowNum++] = new CAvoidSprite(x, y, autoWidth, autoHeight, 2.5, 2.5, &imgHeart, winRect, 0, 1);
		create_mark2++;
	}
}

void paint()
{
	beginPaint();
	clearDevice();
	int i = 0;
	for (i = 0; i < nowNum; ++i)
	{
		if (autosprite[i])
		{
			autosprite[i]->drawSprite();
		}
	}
	if (usr)
	{
		switch (usr->getScore()/5)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			getBigger_mark = 0;
			usr->drawSprite();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			if (getBigger_mark != 1)usr->getBigger(1.15);
			getBigger_mark = 1;
			usr->drawSprite();
			break;
		case 10:
		default:
			if (getBigger_mark != 2)usr->getBigger(1.3);
			getBigger_mark = 2;
			usr->drawSprite();
			break;
		}
		
		char txt[50];
		sprintf_s(txt, "scores:%d    heart:%d", usr->getScore(), usr->getHeart());
		setTextSize(20);
		paintText(10, 10, txt);
	}
	endPaint();
}

void keyEvent(int key, int event)
{
	if (event != KEY_DOWN)return;
	if (begin_mark==1&&(key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT||key== VK_SPACE)) {
		if (key == VK_SPACE) {
			begin_mark2 *= -1;
			if (begin_mark2 == -1) {
				cancelTimer(0);
				cancelTimer(1);
			}
			else {
				startTimer(0, 40);
				startTimer(1, 1000);
			}
		}
		else {
			if (begin_mark2 == 1) {
				if (usr)usr->move(key);
				for (int i = 0; i < nowNum; ++i)
				{
					if (autosprite[i])
					{
						if (usr->collision(autosprite[i]->getRect()))
						{
							int s = autosprite[i]->getScore();
							int t = autosprite[i]->getHeart();
							if (usr) {
								usr->addScore(s);
								usr->addHeart(t);
							}
							delete(autosprite[i]);
							autosprite[i] = NULL;
						}
					}
				}
			}
		}
	}
	if(begin_mark==0){
		begin_mark = 1;
	}
	paint();
}
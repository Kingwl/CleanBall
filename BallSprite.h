#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class BallSprite :public Sprite
{
public:
	static const int red = 0;
	static const int purple = 1;
	static const int pink = 2;
	static const int orange = 3;
	static const int green = 4;
	static const int blue = 5;
	BallSprite();
	~BallSprite();
	static BallSprite* createBall(int type);
	virtual bool init();
	static BallSprite* create(std::string str)
	{
		auto p = new BallSprite();
		if (p && p->initWithFile(str))
		{
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}
	void setPos(Point p);
	Point getPos();
private:
	int x;
	int y;
};


#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class BallSprite :public Sprite
{
public:
	static const int red = 1;
	static const int purple = 2;
	static const int pink = 3;
	static const int orange = 4;
	static const int green = 5;
	static const int blue = 6;
	BallSprite();
	~BallSprite();
	static BallSprite* createBall(int type);
	static BallSprite* createRandomBall();
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
	void flash();
	void flashStop();
	int getPosX();
	int getPosY();
	int getType(){ return m_type; };
	void setType(int n){
		m_type = n;
	}
private:
	int x;
	int y;
	int m_type;
};


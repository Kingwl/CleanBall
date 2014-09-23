#include "BallSprite.h"


BallSprite::BallSprite() :x(0), y(0)
{
}

BallSprite::~BallSprite()
{

}
BallSprite* BallSprite::createBall(int type)
{
	BallSprite *sp;
	switch (type)
	{
	case red:
		sp = BallSprite::create("red.png");
		break;
	case purple:
		sp = BallSprite::create("purple.png");
		break;
	case pink:
		sp = BallSprite::create("pink.png");
		break;
	case orange:
		sp = BallSprite::create("orange.png");
		break;
	case green:
		sp = BallSprite::create("green.png");
		break;
	case blue:
		sp = BallSprite::create("blue.png");
		break;
	}
	return sp;
}
bool BallSprite::init()
{

	return true;
}

void BallSprite::setPos(Point p)
{
	x = p.x;
	y = p.y;
	this->setPosition(ccp(x*30, y*30));
}

Point BallSprite::getPos()
{
	return ccp(x, y);
}
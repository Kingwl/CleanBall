#include "BallSprite.h"


BallSprite::BallSprite() :x(0), y(0)
{
}

BallSprite::~BallSprite()
{

}
BallSprite* BallSprite::createBall(int t_type)
{
	BallSprite *sp = nullptr;
	switch (t_type)
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

	sp->setAnchorPoint(ccp(0, 0));
	sp->setType(t_type);
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
	this->setPosition(ccp(x*30+1, y*30+1));
}

BallSprite* BallSprite::createRandomBall()
{
	int i = 1 + rand() % 6;
	return createBall(i);
}
void BallSprite::flash()
{
	auto flash1 = ScaleTo::create(0.5, 1, 0.5);
	auto flash2 = ScaleTo::create(0.5, 1,1);
	auto flash = Sequence::create(flash1, flash2,nullptr);
	flash->setTag(0x1f);
	this->runAction(flash);
}
void BallSprite::flashStop()
{
	this->stopActionByTag(0x1f);
	this->setScale(1, 1);
}
int BallSprite::getPosX()
{
	return x;
}
int BallSprite::getPosY()
{
	return y;
}